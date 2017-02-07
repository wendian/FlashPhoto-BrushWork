/*******************************************************************************
 * Name            : opaqueapply.cc
 * Project         : BrushWork
 * Description     : cc file for the OpaqueApply
 * Copyright       : Group C05
 * Creation Date   : 10/15/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/opaqueapply.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
OpaqueApply::OpaqueApply(void) {}

OpaqueApply::~OpaqueApply(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void OpaqueApply::ApplyTool(int mask_h, int mask_w, float ** mask,
                            ColorData tool_color,
                            int x, int y, PixelBuffer *canvas) {
  int i, j;
  int cur_x, cur_y;

  // sets x and y bounds relative to center of mask
  int x_bound = mask_w / 2;
  int y_bound = mask_h / 2;

  // put canvas size in variables to reduce function calls
  int canvas_h = canvas->height();
  int canvas_w = canvas->width();

  // calculate where the new pixels would be
  for (i = x_bound * -1; i <= x_bound; i++) {
    for (j = y_bound * -1; j <= y_bound; j++) {
      // calculate where exactly on the canvas we want to be
      cur_x = x + i;
      cur_y = y + j;

      // make sure it's in bounds
      if (!((cur_x < 0) || (cur_x >= canvas_w))) {
        if (!((cur_y < 0) || (cur_y >= canvas_h))) {
          // mask pixel is either 0 or 1, if it is 1 then apply
          // if mask value is 0, don't do anything
          if (mask[i + x_bound][j + y_bound]) {
            canvas->set_pixel(cur_x, cur_y, tool_color);
          }
        }
      }
    }
  }
}

}  // namespace image_tools
