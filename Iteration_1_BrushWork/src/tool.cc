/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Description     : cc file for the Tool abstract class
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/tool.h"
#include <iostream>
#include <cmath>

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
Tool::Tool(void) {}

Tool::~Tool(void) {
  for (int i = 0; i < mask_width_; i++) {
    delete mask_[i];
  }
  delete mask_;
  if (apply_function_ != NULL) delete apply_function_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

  /*
   *  For now, 0 = Pen, 1 = Caligraphy, 2 = Highlighter, 3 = Spray,
   *  4 = Eraser, 5 = Blur
   */

float **Tool::getMask(void) {
  return mask_;
}

void Tool::setApplyFunc(ApplyFunc *new_function) {
  if (apply_function_ != NULL) delete apply_function_;
  apply_function_ = new_function;
}

void Tool::apply(ColorData tool_color, int x, int y, PixelBuffer *canvas) {
    if (apply_function_ != NULL)
      apply_function_->ApplyTool(mask_height_, mask_width_, mask_, tool_color,
                                 x, y, canvas);
}

}  // namespace image_tools
