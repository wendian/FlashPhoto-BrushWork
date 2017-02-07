/*******************************************************************************
 * Name            : f_sharpen.cc
 * Project         : FlashPhoto
 * Module          : Sharpen Filter
 * Description     : Implementation of Sharpen Filter sub class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/10/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/f_sharpen.h"
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

FSharpen::FSharpen(void) : current_sharpen_amount_(0.0) {
  set_complex(1);
  kernel(nullptr);
}

FSharpen::FSharpen(float sharpen_amount) :
  current_sharpen_amount_(sharpen_amount) {
  set_complex(1);
  kernel(MakeKernel());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Kernel *FSharpen::MakeKernel(void) {
  int radius = static_cast<int>(current_sharpen_amount_ / 4);
  Kernel * current_kernel = new Kernel(radius * 2 + 1);
  int kernel_size = current_kernel->length();
  float neg1s = 0;
  float distanceFromCenter;

  for (int i = 0; i < kernel_size; i++) {
    /// loop draws a circle
    int abx2 = i - radius;
    abx2 *= abx2;
    for (int j = 0; j < kernel_size; j++) {
      int aby2 = j - radius;
      aby2 *= aby2;
      distanceFromCenter = sqrt(abx2 + aby2);
      if (distanceFromCenter > radius) {
        current_kernel->set_value(i, j, 0.0);
      } else {
        current_kernel->set_value(i, j, -1.0);
        neg1s += 1.0;
      }
      /**
      /// this only draws a square
      current_kernel->set_value(i, j, -1.0);
      neg1s += 1.0;
      */
    }
  }

  current_kernel->set_value(kernel_size / 2, kernel_size / 2, neg1s);
  return current_kernel;
}

}  /** namespace image_tools */
