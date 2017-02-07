/*******************************************************************************
 * Name            : filter_manager.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of FilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/filter_manager.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include "include/ui_ctrl.h"
#include "include/filter.h"
#include "include/f_blur.h"
#include "include/f_motion_blur.h"
#include "include/f_edge_detect.h"
#include "include/f_sharpen.h"
#include "include/f_saturate.h"
#include "include/f_threshold.h"
#include "include/f_channels.h"
#include "include/f_quantize.h"
#include "include/f_colorswap.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FilterManager::FilterManager(void) :
    channel_color_red_(0.0),
    channel_color_green_(0.0),
    channel_color_blue_(0.0),
    saturation_amount_(0.0),
    threshold_amount_(0.0),
    blur_amount_(0.0),
    sharpen_amount_(0.0),
    motion_blur_amount_(0.0),
    motion_blur_direction_(UICtrl::UI_DIR_E_W),
    quantize_bins_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void FilterManager::ApplyChannel(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Channels with red = "
            << channel_color_red_
            << ", green = " << channel_color_green_
            << ", blue = " << channel_color_blue_ << std::endl;

  Filter * f = new FChannels(channel_color_red_,
                             channel_color_green_,
                             channel_color_blue_);
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::ApplySaturate(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Saturate with amount = "
            << saturation_amount_ << std::endl;

  Filter * f = new FSaturate(saturation_amount_);
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::ApplyBlur(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Blur with amount = "
            << blur_amount_ << std::endl;

  if (blur_amount_ > 0) {
    Filter * f = new FBlur(blur_amount_);
    f->FilterApply(buffer);
    delete f;
  }
}

void FilterManager::ApplySharpen(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << sharpen_amount_ << std::endl;

  if (sharpen_amount_ > 0) {
    Filter * f = new FSharpen(sharpen_amount_);
    f->FilterApply(buffer);
    delete f;
  }
}

void FilterManager::ApplyMotionBlur(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Motion Blur with amount = "
            << motion_blur_amount_
            << " and direction " << motion_blur_direction_ << std::endl;

  if (motion_blur_amount_ > 0) {
    Filter * f = new FMotionBlur(motion_blur_amount_, motion_blur_direction_);
    f->FilterApply(buffer);
    delete f;
  }
}

void FilterManager::ApplyEdgeDetect(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Edge Detect" << std::endl;
  Filter *f = new FEdgeDetect();
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::ApplyQuantize(PixelBuffer *buffer) {
  std::cout << "Apply has been clicked for Quantize with bins = "
            << quantize_bins_ << std::endl;

  Filter * f = new FQuantize(quantize_bins_);
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::ApplyThreshold(PixelBuffer *buffer) {
  std::cout << "Apply Threshold has been clicked with amount = "
            << threshold_amount_ << std::endl;

  Filter * f = new FThreshold(threshold_amount_);
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::ApplySpecial(PixelBuffer *buffer) {
  std::cout << "Apply Color Swap has been clicked" << std::endl;

  Filter * f = new FColorswap();
  f->FilterApply(buffer);
  delete f;
}

void FilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddBlurToGLUI(filter_panel, s_gluicallback);
    AddMotionBlurToGLUI(filter_panel, s_gluicallback);
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);

    new GLUI_Column(filter_panel, true);

  AddSaturationToGLUI(filter_panel, s_gluicallback);
  AddChannelToGLUI(filter_panel, s_gluicallback);
  AddQuantizationToGLUI(filter_panel, s_gluicallback);

    /// YOUR SPECIAL FILTER PANEL
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filter_panel,
                                                    "Color Swap");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }
} /** FilterManager::InitGlui() */

void FilterManager::AddBlurToGLUI(GLUI_Panel *filter_panel,
                                  void (*s_gluicallback)(int)) {
  GLUI_Panel *blur_panel = new GLUI_Panel(filter_panel, "Blur");
  GLUI_Spinner * blur_amount = new GLUI_Spinner(blur_panel, "Amount:",
                                                &blur_amount_);
  blur_amount->set_int_limits(0, 20);
  blur_amount->set_int_val(5);

  new GLUI_Button(blur_panel, "Apply",
                  UICtrl::UI_APPLY_BLUR, s_gluicallback);
}

void FilterManager::AddMotionBlurToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
  GLUI_Panel *motion_blur_panel = new GLUI_Panel(filter_panel, "MotionBlur");
  GLUI_Spinner*motion_blur_amount = new GLUI_Spinner(motion_blur_panel,
                                                     "Amount:",
                                                     &motion_blur_amount_);
  motion_blur_amount->set_int_limits(0, 100);
  motion_blur_amount->set_int_val(5);

  motion_blur_direction_ = UICtrl::MotionBlurDirection::UI_DIR_N_S;
  GLUI_RadioGroup *dir_blur = new GLUI_RadioGroup(
      motion_blur_panel,
      reinterpret_cast<int*>(&motion_blur_direction_));
  new GLUI_RadioButton(dir_blur, "North/South");
  new GLUI_RadioButton(dir_blur, "East/West");
  new GLUI_RadioButton(dir_blur, "NorthEast/SouthWest");
  new GLUI_RadioButton(dir_blur, "NorthWest/SouthEast");

  new GLUI_Button(motion_blur_panel, "Apply",
                  UICtrl::UI_APPLY_MOTION_BLUR, s_gluicallback);
}

void FilterManager::AddSharpenToGLUI(GLUI_Panel *filter_panel,
                                     void (*s_gluicallback)(int)) {
  GLUI_Panel *sharpen_panel = new GLUI_Panel(filter_panel, "Sharpen");
      GLUI_Spinner * sharp_amount = new GLUI_Spinner(sharpen_panel,
                                                     "Amount:",
                                                     &sharpen_amount_);
      sharp_amount->set_int_limits(0, 100);
      sharp_amount->set_int_val(5);

      new GLUI_Button(sharpen_panel, "Apply",
                      UICtrl::UI_APPLY_SHARP, s_gluicallback);
}

void FilterManager::AddEdgeDetectToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
GLUI_Panel *edge_det_panel = new GLUI_Panel(filter_panel, "Edge Detect");
  new GLUI_Button(edge_det_panel, "Apply",
                  UICtrl::UI_APPLY_EDGE, s_gluicallback);
}

void FilterManager::AddThresholdToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
  GLUI_Panel *thres_panel = new GLUI_Panel(filter_panel, "Threshold");
  GLUI_Spinner *threshold_amount = new GLUI_Spinner(thres_panel,
                                                    "Level:",
                                                    &threshold_amount_);
  threshold_amount->set_float_limits(0, 1);
  threshold_amount->set_float_val(0.5);

  new GLUI_Button(thres_panel, "Apply",
                  UICtrl::UI_APPLY_THRESHOLD, s_gluicallback);
}

void FilterManager::AddSaturationToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Saturation");
  GLUI_Spinner * saturation_amount = new GLUI_Spinner(satur_panel,
                                                      "Amount:",
                                                      &saturation_amount_);
  saturation_amount->set_float_limits(-10, 10);
  saturation_amount->set_float_val(1);

  new GLUI_Button(satur_panel, "Apply",
                  UICtrl::UI_APPLY_SATURATE,
                  s_gluicallback);
}

void FilterManager::AddChannelToGLUI(GLUI_Panel *filter_panel,
                                        void (*s_gluicallback)(int)) {
    GLUI_Panel *channel_panel = new GLUI_Panel(filter_panel, "Channels");
      GLUI_Spinner *channel_red = new GLUI_Spinner(channel_panel, "Red:",
                                                   &channel_color_red_);
      GLUI_Spinner *channel_green = new GLUI_Spinner(channel_panel,
                                                     "Green:",
                                                     &channel_color_green_);
      GLUI_Spinner *channel_blue = new GLUI_Spinner(channel_panel,
                                                    "Blue:",
                                                    &channel_color_blue_);

      channel_red->set_float_limits(0, 10);
      channel_red->set_float_val(1);
      channel_green->set_float_limits(0, 10);
      channel_green->set_float_val(1);
      channel_blue->set_float_limits(0, 10);
      channel_blue->set_float_val(1);

      new GLUI_Button(channel_panel, "Apply",
                      UICtrl::UI_APPLY_CHANNEL,
                      s_gluicallback);
}

void FilterManager::AddQuantizationToGLUI(GLUI_Panel *filter_panel,
                                          void (*s_gluicallback)(int)) {
  GLUI_Panel *quant_panel = new GLUI_Panel(filter_panel, "Quantize");
  GLUI_Spinner * quantize_bins = new GLUI_Spinner(quant_panel, "Bins:",
                                                      &quantize_bins_);
  quantize_bins->set_int_limits(2, 256);
  quantize_bins->set_int_val(8);
  quantize_bins->set_speed(0.1);

  new GLUI_Button(quant_panel, "Apply",
                  UICtrl::UI_APPLY_QUANTIZE,
                  s_gluicallback);
}

}  /** namespace image_tools */
