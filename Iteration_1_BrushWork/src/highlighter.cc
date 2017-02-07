/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Description     : cc file for Highlighter
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/highlighter.h"
#include "include/transapply.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/

Highlighter::Highlighter(void) {
  InitMask();
  setApplyFunc(new TransApply());
}

/*******************************************************************************
* Member Functions
******************************************************************************/

void Highlighter::InitMask(void) {
  mask_width_ = 5;
  mask_height_ = 15;
  mask_ = new float*[mask_width_];
  for (int i = 0; i < mask_width_; i++) {
    mask_[i] = new float[mask_height_] ();
  }
  for (int x = 0; x < mask_width_; x++) {
    for (int y = 0; y < mask_height_; y++) {
      mask_[x][y] = 0.4;
    }
  }
}

}  // namespace image_tools
