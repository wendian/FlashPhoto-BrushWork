/*******************************************************************************
 * Name            : f_sharpen.h
 * Project         : image_tools
 * Module          : Sharpen Filter
 * Description     : Header file for Sharpen Filter subclass
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/10/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_

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
 * @brief Implements a convolutional based sharpening filter using a
 * corresponding kernel
 *
 */
class FSharpen : public Filter {
 public:
  FSharpen(void);
  explicit FSharpen(float sharpen_amount);

 private:
  Kernel *MakeKernel(void);

  const float current_sharpen_amount_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_SHARPEN_H_
