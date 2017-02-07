/*******************************************************************************
 * Name            : spraycan.cc
 * Project         : BrushWork
 * Description     : cc file for SprayCan
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/spraycan.h"
#include <cmath>
#include "include/transapply.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

SprayCan::SprayCan(void) {
  InitMask();
  setApplyFunc(new TransApply());
}

/*******************************************************************************
* Member Functions
******************************************************************************/

void SprayCan::InitMask(void) {
  // 28.28 is the maximum distance from center of the mask
  // This means we take the distance from center divided by the maximum
  // distance to get a ratio of how opaque it should be, multiply
  // it by .2 to normalize that to the maximum spray can opacity
  // and subtract that value from .2
  mask_width_ = 41;
  mask_height_ = 41;
  float opacity;
  float distanceFromCenter;
  mask_ = new float*[mask_width_];
  for (int i = 0; i < mask_width_; i++) {
    mask_[i] = new float[mask_height_] ();
  }

  for (int x = 0; x < mask_width_; x++) {
    for (int y = 0; y < mask_height_; y++) {
      distanceFromCenter = sqrt((x-20)*(x-20) + (y-20)*(y-20));
      opacity = 0.2 - 0.2 * (distanceFromCenter / 28.28);

      if (distanceFromCenter > 20) mask_[x][y] = 0.0;
      else mask_[x][y] = opacity;
    }
  }
}

}  // namespace image_tools
