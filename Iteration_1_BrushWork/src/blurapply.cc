/*******************************************************************************
 * Name            : blurapply.cc
 * Project         : BrushWork
 * Description     : Source code for BlurApply: Blur tool masking
 * Copyright       : Group C05
 * Creation Date   : 10/15/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/blurapply.h"
#include <cmath>

namespace image_tools {

/*******************************************************************************
 * Constructors/ Destructors
 ******************************************************************************/

BlurApply::BlurApply(void) {}

BlurApply::~BlurApply(void) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void BlurApply::ApplyTool(int mask_h, int mask_w, float ** mask,
                          ColorData tool_color,
                          int x, int y, PixelBuffer *canvas) {
  int i, j, k, l;
  int cur_x, cur_y;
  int bubl_x, bubl_y;
  ColorData color;

  int x_bound = mask_w / 2;  // sets x and y bounds
  int y_bound = mask_h / 2;

  int canvas_h = canvas->height();
  int canvas_w = canvas->width();

  // variable to keep track of average rgb values
  float nValidPixels;
  // nValidPixels is float to avoid typcasting, which may slow down calculations
  float tempR, tempG, tempB;

  // calculate guassian blur for each pixel in mask
  for (i = x_bound * -1; i <= x_bound; i++) {
    for (j = y_bound * -1; j <= y_bound; j++) {
      // calculate where exactly on the canvas we want to be
      cur_x = x + i;
      cur_y = y + j;

      if (!((cur_x < 0) || (cur_x >= canvas_w))) {
        if (!((cur_y < 0) || (cur_y >= canvas_h))) {
          // Create a 3x3 bubble around the current pixel to calculate blur
          nValidPixels = 0;
          tempR = 0;
          tempG = 0;
          tempB = 0;
          for (k = -1; k <= 1; k++) {
            for (l = -1; l <= 1; l++) {
              bubl_x = cur_x + k;
              bubl_y = cur_y + l;

              // check if bubble coordinate is in canvas bounds
              if (!((bubl_x < 0) || (bubl_x >= canvas_w))) {
                if (!((bubl_y < 0) || (bubl_y >= canvas_h))) {
                  nValidPixels += 1.0;
                  tempR += canvas->get_pixel(bubl_x, bubl_y).red();
                  tempG += canvas->get_pixel(bubl_x, bubl_y).green();
                  tempB += canvas->get_pixel(bubl_x, bubl_y).blue();
                }
              }
            }
          }
          color = ColorData(tempR / nValidPixels, tempG / nValidPixels,
                            tempB / nValidPixels)
                            * mask[i+x_bound][j+y_bound];
          canvas->set_pixel(cur_x, cur_y, color);
        }
      }
    }
  }
}

}  // namespace image_tools
