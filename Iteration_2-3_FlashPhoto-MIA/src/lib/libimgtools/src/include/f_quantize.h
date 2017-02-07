/*******************************************************************************
 * Name            : f_quantize.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header for quantize class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/11/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

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
 * @brief Implements a quantization filter
 *
 * Reduce the amount of information comprising an image by sorting each pixel
 * into one of n predefined bins that cover the full range of RGB (0.0-1.0).
 *
 */
class FQuantize : public Filter {
 public:
  explicit FQuantize(int bins);

 private:
  ColorData SimpleModifyPixel(const ColorData &old_color);

  /**
   * @brief Does the main work to place the color into a bin
   */
  float classify_comp(float comp);

  /**
   * @brief There are n-1 separators for n bins
   */
  const float separators_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_QUANTIZE_H_
