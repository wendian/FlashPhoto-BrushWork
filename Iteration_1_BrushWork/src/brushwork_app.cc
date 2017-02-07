/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/brushwork_app.h"
#include <cmath>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int width,
                           int height)
  : BaseGfxApp(width,
               height),
    display_buffer_(nullptr),
    cur_tool_(0.0),
    cur_color_red_(0.0),
    cur_color_green_(0.0),
    cur_color_blue_(0.0),
    spinner_r_(nullptr),
    spinner_g_(nullptr),
    spinner_b_(nullptr) {}

BrushWorkApp::~BrushWorkApp(void) {
  if (display_buffer_) {
      delete display_buffer_;
  }
  for (int i = 0; i < 6; i++) {
    delete toolbox_[i];
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BrushWorkApp::Init(int argc, char* argv[],
                        int x, int y,
                        ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("BrushWork");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();
  InitTools();
}

// Recursively paints the midpoint between two clicks
// Looks like a preorder binary tree traversal
void BrushWorkApp::ApplyBetween(int start_x, int start_y,
                                int end_x, int end_y) {
  int dx = start_x - end_x;
  if (dx < 0) dx *= -1;
  int dy = start_y - end_y;
  if (dy < 0) dy *= -1;

  // Calculate the distance traveled, if not travelled more than 1
  // in any direction, just return
  if (dx <= 1 && dy <= 1) return;

  int mid_x = start_x;
  int mid_y = start_y;

  // Find where the midpoint is
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

  toolbox_[cur_tool_]->apply(ColorData(cur_color_red_,
                                       cur_color_green_,
                                       cur_color_blue_),
                              mid_x, mid_y, display_buffer_);

  // Recursive call, the space between the midpoint may still be blank
  ApplyBetween(start_x, start_y, mid_x, mid_y);
  ApplyBetween(mid_x, mid_y, end_x, end_y);
}

void BrushWorkApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void BrushWorkApp::MouseDragged(int x, int y) {
  ApplyBetween(prev_x_, prev_y_, x, y);
  toolbox_[cur_tool_]->apply(ColorData(cur_color_red_,
                                       cur_color_green_,
                                       cur_color_blue_), x, y, display_buffer_);
  prev_x_ = x;
  prev_y_ = y;
}

void BrushWorkApp::MouseMoved(int x, int y) { }

void BrushWorkApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
  toolbox_[cur_tool_]->apply(ColorData(cur_color_red_,
                                       cur_color_green_,
                                       cur_color_blue_), x, y, display_buffer_);
  prev_x_ = x;
  prev_y_ = y;
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
  int offset = display_buffer_->height();
  y = offset - y;
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void BrushWorkApp::InitializeBuffers(ColorData background_color,
                                     int width,
                                     int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void BrushWorkApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                               &cur_tool_,
                                               UI_TOOLTYPE,
                                               s_gluicallback);

  // Create interface buttons for different tools:
  new GLUI_RadioButton(radio, "Pen");
  new GLUI_RadioButton(radio, "Caligraphy Pen");
  new GLUI_RadioButton(radio, "Highlighter");
  new GLUI_RadioButton(radio, "Spray Can");
  new GLUI_RadioButton(radio, "Eraser");
  new GLUI_RadioButton(radio, "Blur");

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");

  cur_color_red_ = 0;
  spinner_r_  = new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                                 UI_COLOR_R, s_gluicallback);
  spinner_r_->set_float_limits(0, 1.0);

  cur_color_green_ = 0;
  spinner_g_ = new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                                 UI_COLOR_G, s_gluicallback);
  spinner_g_->set_float_limits(0, 1.0);

  cur_color_blue_ = 0;
  spinner_b_  = new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                                 UI_COLOR_B, s_gluicallback);
  spinner_b_->set_float_limits(0, 1.0);
  new GLUI_Button(color_panel, "Red", UI_PRESET_RED, s_gluicallback);
  new GLUI_Button(color_panel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
  new GLUI_Button(color_panel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
  new GLUI_Button(color_panel, "Green", UI_PRESET_GREEN, s_gluicallback);
  new GLUI_Button(color_panel, "Blue", UI_PRESET_BLUE, s_gluicallback);
  new GLUI_Button(color_panel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
  new GLUI_Button(color_panel, "White", UI_PRESET_WHITE, s_gluicallback);
  new GLUI_Button(color_panel, "Black", UI_PRESET_BLACK, s_gluicallback);


  new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
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

void BrushWorkApp::InitTools() {
  toolbox_[0] = new Pen();
  toolbox_[1] = new CalligraphyPen();
  toolbox_[2] = new Highlighter();
  toolbox_[3] = new SprayCan();
  toolbox_[4] = new Eraser();
  toolbox_[5] = new Blur();
}

void BrushWorkApp::GluiControl(int control_id) {
  switch (control_id) {
  case UI_PRESET_RED:
    cur_color_red_ = 1;
    cur_color_green_ = 0;
    cur_color_blue_ = 0;
    break;
  case UI_PRESET_ORANGE:
    cur_color_red_ = 1;
    cur_color_green_ = 0.5;
    cur_color_blue_ = 0;
    break;
  case UI_PRESET_YELLOW:
    cur_color_red_ = 1;
    cur_color_green_ = 1;
    cur_color_blue_ = 0;
    break;
  case UI_PRESET_GREEN:
    cur_color_red_ = 0;
    cur_color_green_ = 1;
    cur_color_blue_ = 0;
    break;
  case UI_PRESET_BLUE:
    cur_color_red_ = 0;
    cur_color_green_ = 0;
    cur_color_blue_ = 1;
    break;
  case UI_PRESET_PURPLE:
    cur_color_red_ = 0.5;
    cur_color_green_ = 0;
    cur_color_blue_ = 1;
    break;
  case UI_PRESET_WHITE:
    cur_color_red_ = 1;
    cur_color_green_ = 1;
    cur_color_blue_ = 1;
    break;
  case UI_PRESET_BLACK:
    cur_color_red_ = 0;
    cur_color_green_ = 0;
    cur_color_blue_ = 0;
    break;
  default:
    break;
  }

  spinner_b_->set_float_val(cur_color_blue_);
  spinner_g_->set_float_val(cur_color_green_);
  spinner_r_->set_float_val(cur_color_red_);
}
}  // namespace image_tools
