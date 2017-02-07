/*******************************************************************************
 * Name            : t_stamp.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for TStamp class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/19/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_STAMP_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_STAMP_H_

/*******************************************************************************
 * Include Definitions
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/tool.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A stamp tool that is meant to be applied in a "click" rather than a
 * "click and drag" motion like all the other canvas tools. It can stamp images
 * of any size onto the canvas. The stamp image must be explicitly set to use.
 *
 */
class TStamp : public Tool {
 public:
  TStamp(void);
  virtual ~TStamp(void);

  void ApplyToBuffer(int tool_x, int tool_y,
                     ColorData tool_color,
                     PixelBuffer *buffer);

  void set_stamp_buffer(const PixelBuffer &stampBuffer);

  std::string name(void) { return "Stamp"; }

  void stamp_toggle(int state) { stamp_toggle_ = state; }

 private:
  PixelBuffer *stampBuffer_;
  int stamp_toggle_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_T_STAMP_H_
