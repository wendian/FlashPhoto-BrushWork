/*******************************************************************************
 * Name            : f_motion_blur.h
 * Project         : image_tools
 * Module          : Motion Blur Filter
 * Description     : Header file for Motion Blur Filter subclass
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/13/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a motion blurring filter.
 *
 * This is different that a blurring filter, which blurs in all directions. A
 * motion blur filter only blurs in one particular direction. This is a
 * convolutional filter and requires a kernel.
 *
 */
class FMotionBlur : public Filter {
 public:
  FMotionBlur(void);
  FMotionBlur(float blur_amount, enum UICtrl::MotionBlurDirection direction);

 private:
  Kernel *MakeKernel(void);

  const float current_blur_amt_;
  const enum UICtrl::MotionBlurDirection current_direction_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_MOTION_BLUR_H_
