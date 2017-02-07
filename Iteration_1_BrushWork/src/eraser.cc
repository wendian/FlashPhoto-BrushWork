/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Description     : cc file for Eraser
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/eraser.h"
#include <cmath>
#include "include/eraseapply.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Eraser::Eraser(void) {
  InitMask();
  setApplyFunc(new EraseApply());
}


/*******************************************************************************
* Member Functions
******************************************************************************/

void Eraser::InitMask(void) {
  mask_height_ = 21;
  mask_width_ = 21;

  float distanceFromCenter;
  mask_ = new float*[mask_width_];
  for (int i = 0; i < mask_width_; i++) {
    mask_[i] = new float[mask_height_] ();
  }

  for (int x = 0; x < mask_width_; x++) {
    for (int y = 0; y < mask_height_; y++) {
      distanceFromCenter = sqrt((x-10)*(x-10) + (y-10)*(y-10));

      if (distanceFromCenter > 10) mask_[x][y] = 0.0;
      else mask_[x][y] = 1.0;
    }
  }
}

}  // namespace image_tools
