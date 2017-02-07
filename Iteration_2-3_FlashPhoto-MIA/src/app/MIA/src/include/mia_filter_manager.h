/*******************************************************************************
 * Name            : mia_filter_manager.h
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Header for MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_FILTER_MANAGER_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include "lib/libimgtools/src/include/filter_manager.h"
#include "GL/glui.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
  /**
   * @brief Manager for all aspects of filters in MIA, including
   * initialization of GLUI control elements for filters, filter creation,
   * application, deletion.
   */
class MIAFilterManager : public FilterManager {
 public:
  MIAFilterManager();
  ~MIAFilterManager();

  /**
   * @brief Compares two PixelBuffer canvases' height and width.
   *
   * @param[in] First canvas
   * @param[in] Second canvas
   */
  void CompareImages(PixelBuffer *buf1, PixelBuffer *buf2);
  /**
   * @brief parses the arguments and indicates success.
   *
   * @param[in] argc: Number of arguments inputted
   * @param[in] argv: Array of arguments
   */
  bool ParseFilters(int argc, char *argv[]);
  /**
   * @brief Number of current filters for command line mode
   */
  int filter_count() { return filters_.size(); }
  /**
   * @brief Acquires a filter from the filter array at a given index
   */
  Filter *get_filter(int n)
    { return (filters_.empty()) ? nullptr : filters_[n]; }
  /**
   * @brief Initialize the elements of the GLUI interface required by the
   * FilterManager
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   */
  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));

 private:
  /**
   * @brief Converts an int to type float and indicates success
   */
  bool to_float(const std::string &number);
  /**
   * @brief Converts a float to type int and indicates success
   */
  bool to_int(const std::string &number);
  /**
   * @brief Deletes an array of filters.
   */
  void delete_filters(void);

  /// Keep a sequence of options for the command line
  std::vector<Filter*> filters_;
};

}  /** namespace image_tools */
#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_FILTER_MANAGER_H_
