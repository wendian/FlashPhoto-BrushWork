/*******************************************************************************
 * Name            : f_saturate.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for saturate class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Riley Weingarth
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_saturate.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
FSaturate::FSaturate(float saturation_amount) :
  current_sat_(saturation_amount) {
  set_complex(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData FSaturate::SimpleModifyPixel(const ColorData &old_color) {
  float offset = old_color.luminance() * (1 - current_sat_);

  float red = offset + (old_color.red() * current_sat_);
  float green = offset + (old_color.green() * current_sat_);
  float blue = offset + (old_color.blue() * current_sat_);

  return validate_color(red, green, blue, old_color.alpha());
}

} /** namespace image_tools */
