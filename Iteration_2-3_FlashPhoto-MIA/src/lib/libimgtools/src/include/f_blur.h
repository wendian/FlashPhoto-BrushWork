/*******************************************************************************
 * Name            : f_blur.h
 * Project         : image_tools
 * Module          : Blur Filter
 * Description     : Header file for Blur Filter subclass
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/08/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements a blurring convolution filter using a kernel (i.e. blurs
 * equally in all directions).
 */
class FBlur : public Filter {
 public:
  FBlur(void);
  explicit FBlur(float blur_amount);

 private:
  Kernel *MakeKernel(void);

  const float current_blur_amt_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_BLUR_H_
