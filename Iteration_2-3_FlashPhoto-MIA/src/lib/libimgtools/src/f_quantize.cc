/*******************************************************************************
 * Name            : f_quantize.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for quantize class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/11/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_quantize.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

FQuantize::FQuantize(int bins) : separators_(static_cast<float>(bins - 1)) {
  set_complex(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

float FQuantize::classify_comp(float comp) {
  return round(comp * separators_) / separators_;
}

ColorData FQuantize::SimpleModifyPixel(const ColorData &old_color) {
  float red = classify_comp(old_color.red());
  float green = classify_comp(old_color.green());
  float blue = classify_comp(old_color.blue());

  return validate_color(red, green, blue, old_color.alpha());
}

}  /** namespace image_tools */
