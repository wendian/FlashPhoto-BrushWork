/*******************************************************************************
 * Name            : f_blur.cc
 * Project         : FlashPhoto
 * Module          : Blur Filter
 * Description     : Implementation of Blur Filter sub class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/08/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/f_blur.h"
#include <iostream>
#include <cmath>
#include "include/kernel.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FBlur::FBlur(void) : current_blur_amt_(0.0) {
  set_complex(1);
  kernel(nullptr);
}

FBlur::FBlur(float blur_amount) : current_blur_amt_(blur_amount) {
  set_complex(1);
  kernel(MakeKernel());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Kernel *FBlur::MakeKernel(void) {
  int radius = static_cast<int>(current_blur_amt_);
  Kernel * current_kernel = new Kernel(radius * 2 + 1);
  int kernel_size = current_kernel->length();
  float distanceFromCenter;
  float normalizer = 0;

  /// loop draws a circle that gets mroe intense in the center
  for (int i = 0; i < kernel_size; i++) {
    int abx2 = i - radius;
    abx2 *= abx2;
    for (int j = 0; j < kernel_size; j++) {
      int aby2 = j - radius;
      aby2 *= aby2;
      distanceFromCenter = sqrt(abx2 + aby2);
      if (distanceFromCenter > radius) {
        current_kernel->set_value(i, j, 0.0);
      } else {
        current_kernel->set_value(i, j, (radius + 1) - distanceFromCenter);
        normalizer += (radius + 1) - distanceFromCenter;
      }
    }
  }
  if (normalizer > 0.0) {
    float normal_val;
    for (int i = 0; i < kernel_size; i++) {
      for (int j = 0; j < kernel_size; j++) {
        normal_val = current_kernel->get_value(i, j);
        normal_val /= normalizer;
        current_kernel->set_value(i, j, normal_val);
      }
    }
  }
  return current_kernel;
}

}  /** namespace image_tools */
