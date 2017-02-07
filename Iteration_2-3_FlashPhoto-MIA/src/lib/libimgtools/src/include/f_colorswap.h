/*******************************************************************************
 * Name            : f_colorswap.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for FColorswap class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Riley Weingarth
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_COLORSWAP_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_COLORSWAP_H_

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
 * @brief Implements an simple colorswap filter that swaps the RGB values at
 * random.
 *
 */
class FColorswap : public Filter {
 public:
  FColorswap(void);

 private:
  ColorData SimpleModifyPixel(const ColorData &old_color);

  static unsigned int first_seed_;
  const int swap_seed_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_COLORSWAP_H_
