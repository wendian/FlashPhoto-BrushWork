/*******************************************************************************
 * Name            : f_edge_detect.cc
 * Project         : FlashPhoto
 * Module          : Edge Detect Filter
 * Description     : Implementation of Edge Detect Filter sub class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/10/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/f_edge_detect.h"
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

FEdgeDetect::FEdgeDetect(void) {
  set_complex(1);
  kernel(MakeKernel());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Kernel *FEdgeDetect::MakeKernel(void) {
  Kernel * current_kernel = new Kernel(3);
  int kernel_size = current_kernel->length();
  for (int i = 0; i < kernel_size; i++) {
    for (int j = 0; j < kernel_size; j++) {
      current_kernel->set_value(i, j, -1.0);
    }
  }
  current_kernel->set_value(1, 1, 8.0);
  return current_kernel;
}

}  /** namespace image_tools */
