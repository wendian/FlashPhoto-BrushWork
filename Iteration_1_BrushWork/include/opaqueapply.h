/*******************************************************************************
 * Name            : opaqueapply.h
 * Project         : BrushWork
 * Description     : Header file for OpaqueApply: Pen, Calligraphy, and Eraser
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_OPAQUEAPPLY_H_
#define INCLUDE_OPAQUEAPPLY_H_

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

class OpaqueApply : public ApplyFunc {
 public:
  OpaqueApply(void);
  virtual ~OpaqueApply(void);

  void ApplyTool(int mask_h, int mask_w, float **mask,
                 ColorData tool_color,
                 int x, int y, PixelBuffer *canvas);
};

}  // namespace image_tools

#endif  // INCLUDE_OPAQUEAPPLY_H_
