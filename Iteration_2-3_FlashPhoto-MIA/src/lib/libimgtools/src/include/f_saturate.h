/*******************************************************************************
 * Name            : f_saturate.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for saturate class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Riley Weingarth
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a saturation filter
 *
 * A Filter that adjusts the saturation or colorfulness of an image. This can
 * be used to convert an image to grayscale.
 */
class FSaturate : public Filter {
 public:
  explicit FSaturate(float saturation_amount);

 private:
  ColorData SimpleModifyPixel(const ColorData &old_color);

  const float current_sat_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SATURATE_H_
