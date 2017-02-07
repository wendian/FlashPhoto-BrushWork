/*******************************************************************************
 * Name            : t_stamp.cc
 * Project         : image_tools
 * Module          : Filter
 * Description     : Implementation for TStamp class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/19/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_stamp.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
TStamp::TStamp(void) : stampBuffer_(nullptr), stamp_toggle_(0) {
  mask(nullptr);
}

TStamp::~TStamp(void) {
  delete stampBuffer_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void TStamp::ApplyToBuffer(int tool_x, int tool_y,
                           ColorData tool_color,
                           PixelBuffer *buffer) {
  if (stampBuffer_ == nullptr || !stamp_toggle_) return;

  int stamp_w = stampBuffer_->width();
  int stamp_h = stampBuffer_->height();

  int left_bound = std::max(tool_x - stamp_w / 2, 0);
  int right_bound = std::min(tool_x + stamp_w / 2, buffer->width() - 1);
  int lower_bound = std::max(tool_y - stamp_h / 2, 0);
  int upper_bound = std::min(tool_y + stamp_h / 2, buffer->height() - 1);

  ColorData buf_pixel;
  ColorData stamp_pixel;
  float alpha;

  for (int y = lower_bound; y < upper_bound; y++) {
    for (int x = left_bound; x < right_bound; x++) {
      int stamp_x = x - (tool_x - stamp_w / 2);
      int stamp_y = y - (tool_y -  stamp_h / 2);
      stamp_pixel = stampBuffer_->get_pixel(stamp_x, stamp_y);
      alpha = stamp_pixel.alpha();
      buf_pixel = buffer->get_pixel(x, y);
      ColorData new_px = buf_pixel * (1 - alpha) + stamp_pixel * (alpha);
      new_px.alpha(buf_pixel.alpha());
      buffer->set_pixel(x, y, new_px);
    }
  }
}

void TStamp::set_stamp_buffer(const PixelBuffer &stampBuffer) {
  int s_h = stampBuffer.height();
  int s_w = stampBuffer.width();
  delete stampBuffer_;
  stampBuffer_ = new PixelBuffer(s_w, s_h, ColorData());
  *stampBuffer_ = stampBuffer;
  stamp_toggle(1);
}

}  /** namespace image_tools */
