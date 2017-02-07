/*******************************************************************************
 * Name            : filter.cc
 * Project         : FlashPhoto
 * Module          : Filter
 * Description     : Implementation of Filter base class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/06/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/filter.h"
#include "include/kernel.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Filter::Filter(void) : kernel_(nullptr) {}

Filter::~Filter(void) {
  delete kernel_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

ColorData Filter::ApplyKernel(int x, int y,
                             const PixelBuffer &buffer) {
  int buf_w = buffer.width();
  int buf_h = buffer.height();
  /// Set the bounds of the kernel application
  int bound = kernel()->length() / 2;

  float normalizer = 0.0;
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  float alpha;

  ColorData current_pixel = buffer.get_pixel(x, y);
  alpha = current_pixel.alpha();

  /// This part gets you one pixel that is blurred
  /// the kernel is always a square with odd side lengths
  for (int i = bound * -1; i < bound + 1; i++) {
    int buf_y = i + y;
    for (int j = bound * -1; j < bound + 1; j++) {
      int buf_x = j + x;
      float ker_val = kernel()->get_value(j + bound, i + bound);
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
  if (normalizer) {
    red /= normalizer;
    green /= normalizer;
    blue /= normalizer;
  }
  return validate_color(red, green, blue, alpha);
}

ColorData Filter::validate_color(float red, float green, float blue,
                                 float alpha) {
  if (red > 1.0) red = 1.0;
  if (blue > 1.0) blue = 1.0;
  if (green > 1.0) green = 1.0;
  if (red < 0.0) red = 0.0;
  if (green < 0.0) green = 0.0;
  if (blue < 0.0) blue = 0.0;
  return ColorData(red, green, blue, alpha);
}

void Filter::ConvoFilterApply(PixelBuffer *buffer) {
  /// Filters without kernels cannot use this function
  if (kernel_ == nullptr) return;

  int buf_w = buffer->width();
  int buf_h = buffer->height();

  PixelBuffer interim_buf(buf_w, buf_h, ColorData());
  ColorData here_col;

  for (int x = 0; x < buf_w; x++) {
    for (int y = 0; y < buf_h; y++) {
      here_col = ApplyKernel(x, y, *buffer);
      interim_buf.set_pixel(x, y, here_col);
    }
  }
  *buffer = interim_buf;
}

void Filter::SimpleFilterApply(PixelBuffer* buffer) {
  /// Filters with kernels cannot use this function
  if (kernel_ != nullptr) return;
  for (int y = 0; y < buffer->height(); y++) {
    for (int x = 0; x < buffer->width(); x++) {
      ColorData old_color = buffer->get_pixel(x, y);
      buffer->set_pixel(x, y, SimpleModifyPixel(old_color));
    }
  }
}

void Filter::FilterApply(PixelBuffer* buffer) {
  if (is_complex_) {
    ConvoFilterApply(buffer);
  } else {
    SimpleFilterApply(buffer);
  }
}


}  /** namespace image_tools */
