/*******************************************************************************
 * Name            : f_motion_blur.cc
 * Project         : FlashPhoto
 * Module          : Motion Blur Filter
 * Description     : Implementation of Motion Blur Filter sub class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/13/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/f_motion_blur.h"
#include <iostream>
#include <cmath>
#include "include/kernel.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FMotionBlur::FMotionBlur(void) :
  current_blur_amt_(0.0),
  current_direction_(UICtrl::UI_DIR_N_S) {
  set_complex(1);
  kernel(nullptr);
}

FMotionBlur::FMotionBlur(float blur_amount,
                         enum UICtrl::MotionBlurDirection direction) :
  current_blur_amt_(blur_amount),
  current_direction_(direction) {
  set_complex(1);
  kernel(MakeKernel());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Kernel *FMotionBlur::MakeKernel() {
  int diameter = static_cast<int>(current_blur_amt_);
  diameter += !(diameter & 1);
  Kernel * current_kernel = new Kernel(diameter);

  int kernel_size = current_kernel->length();
  float normal_val = 1.0 / kernel_size;

  /// motion blur just draws a line of 1's
  for (int i = 0; i < kernel_size; i++) {
    if (current_direction_ == UICtrl::UI_DIR_N_S) {
      current_kernel->set_value(kernel_size / 2, i, normal_val);
    } else if (current_direction_ == UICtrl::UI_DIR_E_W) {
      current_kernel->set_value(i, kernel_size / 2, normal_val);
    } else if (current_direction_ == UICtrl::UI_DIR_NE_SW) {
      current_kernel->set_value(i, i, normal_val);
    } else {
      current_kernel->set_value(i, kernel_size - i - 1, normal_val);
    }
  }
  return current_kernel;
}
}  /** namespace image_tools */
