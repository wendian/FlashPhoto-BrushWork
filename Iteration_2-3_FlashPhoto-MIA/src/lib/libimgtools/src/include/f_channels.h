/*******************************************************************************
 * Name            : f_channels.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for FChannels class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_CHANNELS_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_CHANNELS_H_

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
 * @brief Filter one or more of the RGB channels, scaling each by the specified
 * amount.
 *
 */
class FChannels : public Filter {
 public:
  FChannels(float ch_red, float ch_green, float ch_blue);

 private:
  ColorData SimpleModifyPixel(const ColorData &old_color);

  const float ch_red_;
  const float ch_green_;
  const float ch_blue_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_CHANNELS_H_
