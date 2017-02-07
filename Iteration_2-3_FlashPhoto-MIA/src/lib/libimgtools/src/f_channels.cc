/*******************************************************************************
 * Name            : f_channels.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for FChannels class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_channels.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
FChannels::FChannels(float ch_red, float ch_green, float ch_blue) :
  ch_red_(ch_red),
  ch_green_(ch_green),
  ch_blue_(ch_blue) {
  set_complex(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData FChannels::SimpleModifyPixel(const ColorData &old_color) {
  float red = old_color.red() * ch_red_;
  float green = old_color.green() * ch_green_;
  float blue = old_color.blue() * ch_blue_;

  return validate_color(red, green, blue, old_color.alpha());
}

}  /** namespace image_tools */
