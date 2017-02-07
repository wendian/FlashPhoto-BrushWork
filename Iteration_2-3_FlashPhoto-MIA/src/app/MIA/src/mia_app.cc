/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_app.h"
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include "lib/libimgtools/src/include/image_handler.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/tool_factory.h"

/** FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height,
               const std::string& marker_fname) : BaseGfxApp(width, height),
                                                  filter_manager_(),
                                                  io_manager_(),
                                                  state_manager_(),
                                                  display_buffer_(nullptr),
                                                  marker_fname_(marker_fname),
                                                  mouse_last_x_(0),
                                                  mouse_last_y_(0),
                                                  pen_(nullptr),
                                                  marker_(nullptr),
                                                  cur_tool_(0),
                                                  inputs_(),
                                                  outputs_(),
                                                  hide_help_(0) {}

MIAApp::MIAApp(void) : BaseGfxApp(1, 1),
                       filter_manager_(),
                       io_manager_(),
                       state_manager_(),
                       display_buffer_(nullptr),
                       marker_fname_(""),
                       mouse_last_x_(0),
                       mouse_last_y_(0),
                       pen_(nullptr),
                       marker_(nullptr),
                       cur_tool_(0),
                       inputs_(),
                       outputs_(),
                       hide_help_(0) {}

MIAApp::~MIAApp(void) {
  if (display_buffer_) delete display_buffer_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  /// Set the name of the window
  set_caption("MIA");

  /// Initialize Interface
  InitializeBuffers(background_color, width(), height());

  pen_ = ToolFactory::CreateTool(ToolFactory::TOOL_PEN);
  assert(pen_);
  marker_ = ToolFactory::CreateTool(ToolFactory::TOOL_STAMP);
  assert(marker_);

  InitGlui();
  InitGraphics();
  io_manager_.file_name(marker_fname_);
  io_manager_.LoadImageToStamp(marker_);
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void MIAApp::help(void) {
  if (hide_help_) return;
  std::cout << "************************************************************\n";
  std::cout << "MIA\n\n";
  std::cout << "Command line mode: MIA <input> <options> <output>\n\n";
  std::cout << "input and output files must be .png or .jpg\n";
  std::cout << "input and output files can also be sequences of images\n";
  std::cout << "In such cases, use the following format file names:\n";
  std::cout << "<sequence_name>###.<extension>\n";
  std::cout << "There must be three # signs and the range will be 000-999\n";
  std::cout << "The output directory MUST already exist\n";
  std::cout << "The following are accepted options:\n";
  std::cout << "-sharpen <float>\n";
  std::cout << "\t[argument must be [0, 100]]\n\n";
  std::cout << "-edge\n";
  std::cout << "-threshold <float>\n";
  std::cout << "\t[argument must be [0, 1]]\n\n";
  std::cout << "-quantize <int>\n";
  std::cout << "\t[argument must be [2, 256]]\n\n";
  std::cout << "-blur <float>\n";
  std::cout << "\t[argument must be [0, 20]]\n\n";
  std::cout << "-saturate <float>\n";
  std::cout << "\t[argument must be [-10, 10]]\n\n";
  std::cout << "-channel <float> <float> <float>\n";
  std::cout << "\t[arguments must be [0, 10]]\n\n";
  std::cout << "-compare\n";
  std::cout << "\t[Checks two images pixel by pixel,\n";
  std::cout << "\tif they differ, it prints 0,";
  std::cout << "otherwise prints 1, \n\t\'output\' is the second image]\n\n";
  std::cout << "If no options given, the input will be saved into output\n\n";
  std::cout << "Using the -nohelp option after the input ";
  std::cout << "will disable the help print\n\n";
  std::cout << "************************************************************\n";
}

bool MIAApp::directory_exists(const std::string path) {
  std::string dir = "./";
  std::string buf = "";
  for (int i = 0; i < path.length(); i++) {
    buf += path[i];
    if (path[i] == '/') {
      dir += buf;
      buf = "";
    }
  }
  struct stat file;
  if (stat(dir.c_str(), &file) == 0) {
    return (file.st_mode & S_IFDIR);
  }
  return false;
}

int MIAApp::Parse(int argc, char* argv[]) {
  std::string current_arg = argv[1];
  if (current_arg.compare("-h") == 0) {
    help();
    return 0;
  }

  if (argc < 3) {
    help();
    return 1;
  }

  std::string input = argv[1];
  std::string output = argv[argc - 1];

  if (!(io_manager_.is_valid_image_file_name(input)
       && io_manager_.is_valid_image_file_name(output))) {
    std::cout << "Bad filenames\n";
    help();
    return 1;
  }

  /// If file is not a stack, check if file exists
  struct stat file;
  bool in_is_stack = input.find("###") != std::string::npos;
  if (!in_is_stack) {
    if (stat(input.c_str(), &file)) {
      std::cout << "Input file does not exist\n";
      help();
      return 1;
    }
  }

  /// Check if the directories exists
  if (!(directory_exists(input) && directory_exists(output))) {
    std::cout << "Input/Output directory does not exist\n";
    help();
    return 1;
  }


  /// First check if the option is compare, it behaves differently
  std::string opt = argv[2];
  if ((opt.compare("-compare") == 0) && (argc == 4)) {
    if (in_is_stack) {
      bool out_is_stack = output.find("###") != std::string::npos;
      if (in_is_stack ^ out_is_stack) {
        std::cout << "In/output do not match (one is a stack, other is not)\n";
        help();
        return 1;
      }
      build_file_names(input, &inputs_);
      build_file_names(output, &outputs_);
      for (int i = 0; i < inputs_.size(); i++) {
        bool in_ex = stat(inputs_[i].c_str(), &file) == 0;
        bool out_ex = stat(outputs_[i].c_str(), &file) == 0;
        if (in_ex && out_ex) {
          display_buffer_ = ImageHandler::LoadImage(inputs_[i]);
          PixelBuffer *comp_buf = ImageHandler::LoadImage(outputs_[i]);
          filter_manager_.CompareImages(display_buffer_, comp_buf);
        }
      }
      return 0;
    } else {
      bool out_exists = stat(output.c_str(), &file) == 0;
      if (out_exists) {
        display_buffer_ = ImageHandler::LoadImage(input);
        PixelBuffer *comp_buf = ImageHandler::LoadImage(output);
        filter_manager_.CompareImages(display_buffer_, comp_buf);
        delete comp_buf;
        return 0;
      } else {
        std::cout << "Compare option was not used properly\n";
        help();
        return 1;
      }
    }
  } else if (opt.compare("-nohelp") == 0) {
    hide_help_ = 1;
  }

  /// Have filter manager parse the filters out
  if (!filter_manager_.ParseFilters(argc, argv)) {
    std::cout << "Filter option was entered incorrectly\n";
    help();
    return 1;
  }

  return loop_thru(input, output);
}

int MIAApp::loop_thru(const std::string &input, const std::string &output) {
  bool in_is_stack = input.find("###") != std::string::npos;
  bool out_is_stack = output.find("###") != std::string::npos;
  if (in_is_stack ^ out_is_stack) {
    std::cout << "Input/output do not match (one is a stack, other is not)\n";
    help();
    return 1;
  }

  if (in_is_stack) {
    std::cout << "Stack of images found" << std::endl;
    /// if it is a stack, we contruct vectors with potential filenames
    build_file_names(input, &inputs_);
    build_file_names(output, &outputs_);
  } else {
    inputs_.push_back(input);
    outputs_.push_back(output);
  }

  struct stat file;
  for (int i = 0; i < inputs_.size(); i++) {
    if (stat(inputs_[i].c_str(), &file) == 0) {
      display_buffer_ = ImageHandler::LoadImage(inputs_[i]);

      for (int j = 0; j < filter_manager_.filter_count(); j++) {
        filter_manager_.get_filter(j)->FilterApply(display_buffer_);
      }
      std::cout << "Saving image:  " << outputs_[i] << std::endl;
      ImageHandler::SaveImage(outputs_[i], display_buffer_);
    }
  }
  return 0;
}

void MIAApp::build_file_names(const std::string &names,
                              std::vector<std::string> *v) {
  int loc = names.find("###");

  std::string front = names.substr(0, loc);
  std::string back  = names.substr(loc + 3);

  std::string number;
  std::string new_name;

  for (int i = 0; i < 1000; i++) {
    number = std::to_string(i);
    while (number.length() < 3) number = "0" + number;
    new_name = front + number + back;
    v->push_back(new_name);
  }
}

/// Recursively paints the midpoint between two clicks
/// Looks like a preorder binary tree traversal
/// This runs faster than the provided solution
void MIAApp::ApplyBetween(int start_x, int start_y,
                          int end_x,   int end_y) {
  int dx = start_x - end_x;
  if (dx < 0) dx *= -1;
  int dy = start_y - end_y;
  if (dy < 0) dy *= -1;

  /// Calculate the distance traveled, if not travelled more than 1
  /// in any direction, just return
  if (dx <= 1 && dy <= 1) return;

  int mid_x = start_x;
  int mid_y = start_y;

  /// Find where the midpoint is
  if (dx > 1) {
    if (start_x < end_x) {
      mid_x = start_x + dx / 2;
    } else {
      mid_x = end_x + dx / 2;
    }
  }
  if (dy > 1) {
    if (start_y < end_y) {
      mid_y = start_y + dy / 2;
    } else {
      mid_y = end_y + dy / 2;
    }
  }
  pen_->ApplyToBuffer(mid_x, height()-mid_y,
                                   ColorData(1.0, 0.0, 0.0),
                                   display_buffer_);
  /// Recursive call, the space between the midpoint may still be blank
  ApplyBetween(start_x, start_y, mid_x, mid_y);
  ApplyBetween(mid_x, mid_y, end_x, end_y);
}

void MIAApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
  state_manager_.UpdateState(*display_buffer_);
  if (cur_tool_ == ToolFactory::TOOL_PEN) {
    pen_->ApplyToBuffer(x, height()-y,
                        ColorData(1.0, 0.0, 0.0),
                        display_buffer_);
  } else {
    marker_->ApplyToBuffer(x, height()-y, ColorData(), display_buffer_);
    marker_->stamp_toggle(0);
  }
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void MIAApp::MouseDragged(int x, int y) {
  if (cur_tool_ == ToolFactory::TOOL_PEN) {
    ApplyBetween(mouse_last_x_, mouse_last_y_, x, y);
    pen_->ApplyToBuffer(x, height()-y,
                        ColorData(1.0, 0.0, 0.0),
                        display_buffer_);
  }
  /// let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void MIAApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
  marker_->stamp_toggle(1);
}

void MIAApp::InitializeBuffers(ColorData background_color,
                               int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void MIAApp::InitGlui(void) {
  /// Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    /// Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

  /** Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));

  /** Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /** Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_BLUR:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplyBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SHARP:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplySharpen(display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplyEdgeDetect(display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplySaturate(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      state_manager_.UpdateState(*display_buffer_);
      filter_manager_.ApplyChannel(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      state_manager_.UpdateState(*display_buffer_);
      io_manager_.LoadImageToCanvas(display_buffer_);
      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_);
      /// Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      state_manager_.ResetState();
      io_manager_.LoadNextImage(display_buffer_);
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      state_manager_.ResetState();
      io_manager_.LoadPreviousImage(display_buffer_);
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                          display_buffer_->height());
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                          display_buffer_->height());
      break;
    default:
      break;
  }

  /// Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}
void MIAApp::InitGraphics(void) {
  /// Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}


}  /** namespace image_tools */
