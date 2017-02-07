/*******************************************************************************
 * Name            : t_blur.cc
 * Project         : FlashPhoto
 * Module          : Tool
 * Description     : Implementation of blur tool class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/13/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_blur.h"
#include <algorithm>
#include "include/m_constant.h"
#include "include/filter.h"
#include "include/f_blur.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TBlur::TBlur(void) {
  small_filter_ = new FBlur(1.0);
  mask(new MConstant(40.0, 1.0));
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData TBlur::ApplyKernel(int x, int y, const PixelBuffer &buffer) {
  int buf_w = buffer.width();
  int buf_h = buffer.height();

  float normalizer = 0.0;
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  float alpha;

  /// Get the alpha value in first
  ColorData current_pixel = buffer.get_pixel(x, y);
  alpha = current_pixel.alpha();
  #pragma omp for
  for (int i = -1; i < 2; i++) {
    int buf_y = i + y;
    for (int j = -1; j < 2; j++) {
      int buf_x = j + x;
      float ker_val = small_filter_->kernel()->get_value(j + 1, i + 1);
      if (ker_val == 0.0) continue;
      if (buf_x >= 0 && buf_x < buf_w && buf_y >= 0 && buf_y < buf_h) {
        current_pixel = buffer.get_pixel(buf_x, buf_y);
        red += ker_val * current_pixel.red();
        green += ker_val * current_pixel.green();
        blue += ker_val * current_pixel.blue();
        normalizer += ker_val;
      }
    }
  }
  red /= normalizer;
  green /= normalizer;
  blue /= normalizer;
  return ColorData(red, green, blue, alpha);
}

void TBlur::RecursiveApply(int layer, int tool_x, int tool_y,
                           PixelBuffer *buffer) {
  int mask_w = mask()->width();
  int mask_h = mask()->height();
  if (layer > mask_w / 2) return;

  int left_bound = std::max(tool_x - mask_w / 2, 0);
  int right_bound = std::min(tool_x + mask_w / 2, buffer->width()-1);
  int lower_bound = std::max(tool_y - mask_h / 2, 0);
  int upper_bound = std::min(tool_y + mask_h / 2, buffer->height()-1);

  PixelBuffer interim_mask(mask_w - layer, mask_h - layer, ColorData());
  int mask_x;
  int mask_y;
  ColorData c;

  for (int y = lower_bound + layer; y <= upper_bound - layer; y++) {
    for (int x = left_bound + layer; x <= right_bound - layer; x++) {
      mask_x = x - (tool_x - mask_w / 2);
      mask_y = y - (tool_y - mask_h / 2);
      if (mask()->value(mask_x, mask_y)) {
        c = ApplyKernel(x, y, *buffer);
      } else {
        c = buffer->get_pixel(x, y);
      }
      interim_mask.set_pixel(mask_x, mask_y, c);
    }
  }

  #pragma omp for
  for (int y = lower_bound + layer; y <= upper_bound - layer; y++) {
    for (int x = left_bound + layer; x <= right_bound - layer; x++) {
      mask_x = x - (tool_x - mask_w / 2);
      mask_y = y - (tool_y - mask_h / 2);
      if (mask()->value(mask_x, mask_y)) {
        c = interim_mask.get_pixel(mask_x, mask_y);
        buffer->set_pixel(x, y, c);
      }
    }
  }
  RecursiveApply(layer +  5, tool_x, tool_y, buffer);
}

void TBlur::ApplyToBuffer(int tool_x, int tool_y,
    ColorData tool_color, PixelBuffer* buffer) {
  RecursiveApply(0, tool_x, tool_y, buffer);
}

}  /** namespace image_tools */
