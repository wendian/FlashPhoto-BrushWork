/*******************************************************************************
 * Name            : calligraphypen.cc
 * Project         : BrushWork
 * Description     : cc file for CalligraphyPen
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/calligraphypen.h"
#include "include/opaqueapply.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
CalligraphyPen::CalligraphyPen(void) {
  InitMask();
  setApplyFunc(new OpaqueApply());
}

/*******************************************************************************
* Member Functions
******************************************************************************/

void CalligraphyPen::InitMask(void) {
  mask_height_ = 15;
  mask_width_ = 5;
  mask_ = new float*[mask_width_];
  for (int i = 0; i < mask_width_; i++) {
    mask_[i] = new float[mask_height_] ();
  }

  for (int x = 0; x < mask_width_; x++) {
    for (int y = 0; y < mask_height_; y++) {
      mask_[x][y] = 1.0;
    }
  }
}

}  // namespace image_tools
