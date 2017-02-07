/*******************************************************************************
> * Name            : mia_app.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIA class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "app/MIA/src/include/mia_filter_manager.h"
#include "app/MIA/src/include/mia_io_manager.h"
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/state_manager.h"
#include "lib/libimgtools/src/include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief The main class for MIA.
 * It is a graphics app that derives from BaseGfxApp. It creates two graphics
 * windows, one for 2D painting and one for the buttons and other UI widgets to
 * control the various features provided by the Applications.
 **/
class MIAApp : public BaseGfxApp {
 public:
  MIAApp(int width, int height, const std::string& marker_fname);
  MIAApp(void);
  virtual ~MIAApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y) {}
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int control_id);

  /**
   * @brief Initialize MIA
   *
   * @param[in] argc Unused--required by BaseGfxApp
   * @param[in] argv Unused--required by BaseGfxApp
   * @param[in] x Unused--required by BaseGfxApp
   * @param[in] y Unused--required by BaseGfxApp
   * @param[in] background_color The initial canvas color
   */
  void Init(
      int argc,
      char *argv[],
      int x,
      int y,
      ColorData background_color);
  /**
   * @brief Parse Command Line input
   *
   * Run when using cmdline mode.
   */
  int Parse(int argc, char* argv[]);

  /// Prints help statement
  void help(void);

 private:
  /// Loops through the input and output names and filters
  int loop_thru(const std::string &input, const std::string &output);

  /// fills the two vectors with names of input and output in sequence
  void build_file_names(const std::string &names, std::vector<std::string> *v);

  /// Indicates whether a given directory exists
  bool directory_exists(const std::string path);

  /// Draw a line between when mouse is dragged
  void ApplyBetween(int start_x, int start_y, int end_x, int end_y);
  /**
   * @brief Initialize the GLUI interface
   *
   */
  void InitGlui(void);
  /**
   * @brief Initialize OpenGL
   *
   */
  void InitGraphics(void);
  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color,
                         int width, int height);

  /** Copy/move assignment/construction disallowed */
  MIAApp(const MIAApp &rhs) = delete;
  MIAApp& operator=(const MIAApp &rhs) = delete;

  /**
   * @brief Manager for all filter operations
   */
  MIAFilterManager filter_manager_;

  /**
   * @brief Manager for all I/O operations
   */
  MIAIOManager io_manager_;

  /**
   * @brief Manager for redo/undo stack
   */
  StateManager state_manager_;

  /// This is the pointer to the buffer where the display PixelBuffer is stored
  PixelBuffer* display_buffer_;

  /// The path to the marker file
  std::string marker_fname_;

  /**
   * @brief This hides the help output when -nohelp is used, mostly used in
   * testing to avoid too much printing
   */
  int hide_help_;

  /// Tells app which tool is selected
  int cur_tool_;

  /// Points to the pen tool, this was a vector in FlashPhoto
  Tool *pen_;

  /// Points to the marker tool, impelmented using the load stamp feature
  Tool *marker_;

  /// Used by apply between to fill in blanks
  int mouse_last_x_;

  /// Used by apply between to fill in blanks
  int mouse_last_y_;

  /// Commandline mode, keeps track of input image file names
  std::vector<std::string> inputs_;

  /// Commandline mode, keeps track of output image file names
  std::vector<std::string> outputs_;
};

}  /** namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_APP_H_
