/*******************************************************************************
 * Name            : f_colorswap.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for FColorswap class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Riley Weingarth
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_colorswap.h"
#include <ctime>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Global Variables
 ******************************************************************************/

unsigned int FColorswap::first_seed_ = 101;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
FColorswap::FColorswap(void) : swap_seed_(rand_r(&first_seed_) % 6) {
  set_complex(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData FColorswap::SimpleModifyPixel(const ColorData &old_color) {
  float red_temp = old_color.red();
  float green_temp = old_color.green();
  float blue_temp = old_color.blue();

  float red;
  float green;
  float blue;

  switch (swap_seed_) {
    case 0:
      red = red_temp;
      green = blue_temp;
      blue = green_temp;
      break;
    case 1:
      red = blue_temp;
      green = red_temp;
      blue = green_temp;
      break;
    case 2:
      red = red_temp;
      green = green_temp;
      blue = blue_temp;
      break;
    case 3:
      red = blue_temp;
      green = green_temp;
      blue = red_temp;
      break;
    case 4:
      red = green_temp;
      green = blue_temp;
      blue = red_temp;
      break;
    case 5:
      red = green_temp;
      green = red_temp;
      blue = blue_temp;
      break;
    default:
      red = red_temp;
      green = green_temp;
      blue = blue_temp;
      break;
  }

  return ColorData(red, green, blue, old_color.alpha());
}

}  /** namespace image_tools */
