/*******************************************************************************
 * Name            : blurapply.h
 * Project         : BrushWork
 * Description     : Header file for Blurapply
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_BLURAPPLY_H_
#define INCLUDE_BLURAPPLY_H_

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/applyfunc.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class BlurApply : public ApplyFunc {
 public:
  BlurApply(void);
  virtual ~BlurApply(void);

  void ApplyTool(int mask_h, int mask_w, float **mask,
                 ColorData tool_color,
                 int x, int y, PixelBuffer *canvas);
  // tool_color will be ignored
};

}  // namespace image_tools

#endif  // INCLUDE_BLURAPPLY_H_
