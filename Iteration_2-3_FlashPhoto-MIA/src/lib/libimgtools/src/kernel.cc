/*******************************************************************************
 * Name            : Kernel.cc
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Implementation of Kernel class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/06/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/kernel.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Kernel::Kernel(void) : radius_(0.0),
               length_(0),
               kernel_array_(nullptr) {}

Kernel::Kernel(int length)
    : radius_(0),
      length_(length) {
    kernel_array_ = new float*[length];
    for (int i = 0; i < length; i++) {
      kernel_array_[i] = new float[length] ();
    }
}

Kernel::~Kernel(void) {
  for (int i = 0; i < length_; i++) {
    delete kernel_array_[i];
  }
  delete kernel_array_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

float Kernel::get_value(int x, int y) const {
  if (kernel_array_ == nullptr ||
      x < 0 || x > length_ ||
      y < 0 || y > length_) {
    return 0.f;
  } else {
    return kernel_array_[x][y];
  }
}

void Kernel::set_value(int x, int y, float v) {
  if (kernel_array_ == nullptr ||
    x < 0 || x > length_ ||
    y < 0 || y > length_) {
    return;
  } else {
    kernel_array_[x][y] = v;
  }
}

}  /** namespace image_tools */
