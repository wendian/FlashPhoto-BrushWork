/*******************************************************************************
 * Name            : applyfunc.h
 * Project         : BrushWork
 * Description     : Header file for ApplyFunc, abstract class for apply styles
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_APPLYFUNC_H_
#define INCLUDE_APPLYFUNC_H_

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class ApplyFunc {
 public:
  ApplyFunc(void);
  virtual ~ApplyFunc(void);

  virtual void ApplyTool(int mask_h, int mask_w, float **mask,
                   ColorData tool_color,
                   int x, int y, PixelBuffer *canvas) = 0;
  // Always overwritten since each tool behaves differently
};

}  // namespace image_tools

#endif  // INCLUDE_APPLYFUNC_H_
