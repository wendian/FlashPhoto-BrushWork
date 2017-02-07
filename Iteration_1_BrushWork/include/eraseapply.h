/*******************************************************************************
 * Name            : eraseapply.h
 * Project         : BrushWork
 * Description     : Header file for EraseApply
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_ERASEAPPLY_H_
#define INCLUDE_ERASEAPPLY_H_

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

class EraseApply : public ApplyFunc {
 public:
  EraseApply(void);
  virtual ~EraseApply(void);

  void ApplyTool(int mask_h, int mask_w, float **mask,
                 ColorData tool_color,
                 int x, int y, PixelBuffer *canvas);
  // tool_color will be ignored
};

}  // namespace image_tools

#endif  // INCLUDE_ERASEAPPLY_H_
