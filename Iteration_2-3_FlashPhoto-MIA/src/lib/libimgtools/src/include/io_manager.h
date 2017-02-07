/*******************************************************************************
 * Name            : io_manager.h
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Header for IoManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IO_MANAGER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IO_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/tool_factory.h"
#include "lib/libimgtools/src/include/t_stamp.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for I/O operations in FlashPhoto. This includes
 * initializing GLUI control elements related to image loading/saving, as well
 * as handling the load/save operations themselves. The load operation includes
 * validating the image type and filesystem permissions before the load will
 * proceed. It also handles loading an image from a file to the stamp.
 */
class IOManager {
 public:
  IOManager();
  ~IOManager() {}

  /**
   * @brief Initialize GLUI control elements for IO management
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   */
  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

  /**
   * @brief Set the image file. If the file is valid, enable loading/saving
   *
   * @param filepath Pathname of the file
   */
  void set_image_file(const std::string & filepath);

  /**
   * @brief Get the current image file name
   *
   * @return The current image file name
   */
  const std::string& file_name(void) { return file_name_;}

  void file_name(std::string f_name) { file_name_ = f_name; }

  /**
   * @brief Get a handle on the GLUI file browser
   *
   * @return The handle
   */
  GLUI_FileBrowser* file_browser(void) { return file_browser_;}

  /**
   * @brief Load the selected image file to the canvas
   *
   */
  virtual void LoadImageToCanvas(PixelBuffer *display_buffer);

  /**
   * @brief Load the selected image file to the stamp
   *
   */
  void LoadImageToStamp(Tool *stamp);

  /**
   * @brief Save the current state of the canvas to a file
   *
   */
  void SaveCanvasToFile(PixelBuffer *display_buffer);

  /**
   * @brief Determine if a file has a valid name for an image file
   *
   * @return TRUE if yes, FALSE otherwise
   */
  bool is_valid_image_file_name(const std::string & name) {
    if (has_suffix(name, ".png") || has_suffix(name, ".jpg")
        || has_suffix(name, ".jpeg")) {
      return true;
    }
    return false;
  }

 protected:
  void AddSaveCanvasToGLUI(GLUI_Panel* image_panel,
                         void (*s_gluicallback)(int));
  void AddLoadStampToGLUI(GLUI_Panel* image_panel,
                          void (*s_gluicallback)(int));
  void AddFileBrowserToGLUI(GLUI_Panel* image_panel,
                            void (*s_gluicallback)(int));

  GLUI_StaticText *current_file_label(void) { return current_file_label_; }

  GLUI_EditText *file_name_box(void) { return file_name_box_; }
  GLUI_StaticText *save_file_label(void) { return save_file_label_; }

  void save_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(save_canvas_btn_, enabled);
  }

  void load_stamp_toggle(bool enabled) {
    UICtrl::button_toggle(load_stamp_btn_, enabled);
  }

  void load_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(load_canvas_btn_, enabled);
  }
  /**
   * @brief Determine if a file name contains a give suffix
   *
   * @return TRUE if yes, FALSE otherwise
   */
  bool has_suffix(const std::string & str, const std::string & suffix) {
    return str.find(suffix, str.length()-suffix.length()) != std::string::npos;
  }

  /**
   * @brief Get the extension AFTER we know it has an extension
   *
   * @return ".<extension>"
   */
  std::string get_img_ext(const std::string &file_name) {
    return file_name.substr(file_name.find('.'), file_name.length());
  }

  /**
   * @brief Helper function to load a PNG file
   */
  PixelBuffer *LoadPNG(const std::string &file_name);

  /**
   * @brief Helper function to load a JPEG file
   */
  PixelBuffer *LoadJPEG(const std::string &file_name);

  /**
   * @brief Helper function to save a PNG file
   */
  void SavePNG(const std::string &file_name, PixelBuffer * display_buffer);

  /**
   * @brief Helper function to save a JPEG file
   */
  void SaveJPEG(const std::string &file_name, PixelBuffer * display_buffer);

  /**
   * @brief Determine if the image corresponding to a given file
   *
   * The file must exist, have a proper suffix, and be openable
   *(i.e. the user
   * has permission to open it).
   *
   * @return TRUE if yes, FALSE otherwise
   */
  bool is_valid_image_file(const std::string &name);

 private:
  /** Copy/move assignment/construction disallowed */
  IOManager(const IOManager &rhs) = delete;
  IOManager& operator=(const IOManager &rhs) = delete;

  /** data members */
  GLUI_FileBrowser *file_browser_;
  GLUI_Button *load_canvas_btn_;
  GLUI_Button *load_stamp_btn_;
  GLUI_Button *save_canvas_btn_;
  GLUI_StaticText *current_file_label_;
  GLUI_EditText *file_name_box_;
  GLUI_StaticText *save_file_label_;
  std::string file_name_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_IO_MANAGER_H_
