/*******************************************************************************
 * Name            : t_blur.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for blur class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/13/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string>
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/f_blur.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool serves as a mobile version of the blur filter, functions
 * much like the spray can, except with blurring neighboring pixels rather than
 * coloring them (linear falloff).
 *
 */

class TBlur : public Tool {
 public:
  TBlur(void);

  void ApplyToBuffer(int tool_x, int tool_y,
                     ColorData tool_color, PixelBuffer *buffer);

  std::string name(void) { return "Blur"; }

 private:
  ColorData ApplyKernel(int x, int y, const PixelBuffer &buffer);

  /**
   * @brief Apply the selected tool to the buffer recursively
   *
   * Function is called by ApplyToBuffer and works as ApplyToBuffer
   * works in the other tools.
   */
  void RecursiveApply(int layer, int tool_x, int tool_y,
                      PixelBuffer *buffer);

  FBlur *small_filter_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_BLUR_H_
