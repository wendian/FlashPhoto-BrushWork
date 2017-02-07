/*******************************************************************************
 * Name            : f_threshold.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for FThreshold class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/filter.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A threshold filter
 *
 * The effect of this filter is to set the RGB components of all pixels that it
 * operates on to 1 if the RGB value is greater than the threshold, and 0
 * otherwise.
 */
class FThreshold : public Filter {
 public:
  explicit FThreshold(float threshold_amount);

 private:
  ColorData SimpleModifyPixel(const ColorData &old_color);

  const float current_threshold_;
};
}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_THRESHOLD_H_
