/*******************************************************************************
 * Name            : transapply.h
 * Project         : BrushWork
 * Description     : Header file for TransApply, class for Spray and Highlighter
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_TRANSAPPLY_H_
#define INCLUDE_TRANSAPPLY_H_

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

class TransApply : public ApplyFunc {
 public:
  TransApply(void);
  virtual ~TransApply(void);

  void ApplyTool(int mask_h, int mask_w, float **mask,
                 ColorData tool_color,
                 int x, int y, PixelBuffer *canvas);
};

}  // namespace image_tools

#endif  // INCLUDE_TRANSAPPLY_H_
