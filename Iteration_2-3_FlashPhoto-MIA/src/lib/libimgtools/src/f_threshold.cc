/*******************************************************************************
 * Name            : f_threshold.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for FThreshold class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/8/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_threshold.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
FThreshold::FThreshold(float threshold_amount) :
  current_threshold_(threshold_amount) {
  set_complex(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData FThreshold::SimpleModifyPixel(const ColorData &old_color) {
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;

  /// Float equlaity comparison isn't very accurate in the first place
  /// Thus >= and > are pretty much the same
  if (old_color.red() > current_threshold_) red = 1.0;
  if (old_color.green() > current_threshold_) green = 1.0;
  if (old_color.blue() > current_threshold_) blue = 1.0;

  return ColorData(red, green, blue, old_color.alpha());
}

}  /** namespace image_tools */
