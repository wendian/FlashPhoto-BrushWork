/*******************************************************************************
 * Name            : mia_filter_manager.cc
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Implementation of MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_filter_manager.h"
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/f_edge_detect.h"
#include "lib/libimgtools/src/include/f_sharpen.h"
#include "lib/libimgtools/src/include/f_blur.h"
#include "lib/libimgtools/src/include/f_quantize.h"
#include "lib/libimgtools/src/include/f_threshold.h"
#include "lib/libimgtools/src/include/f_saturate.h"
#include "lib/libimgtools/src/include/f_channels.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAFilterManager::MIAFilterManager(void) : filters_(), FilterManager() {}

MIAFilterManager::~MIAFilterManager(void) {
  if (!filters_.empty()) {
    delete_filters();
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

bool MIAFilterManager::to_float(const std::string &number) {
  int decimal = 0;
  int i = 0;
  if (number[i] == '-') i++;
  for (; i < number.length(); i++) {
    if (number[i] ==  '.') decimal++;
    else if (number[i] < '0' || number[i] > '9') return false;
  }
  return (decimal < 2 && number.length() > 0);
}

bool MIAFilterManager::to_int(const std::string &number) {
  int i = 0;
  if (number[i] == '-') i++;
  for (; i < number.length(); i++) {
    if (number[i] < '0' || number[i] > '9') return false;
  }
  return true;
}

bool MIAFilterManager::ParseFilters(int argc, char* argv[]) {
  Filter * f = nullptr;
  int i = 2;
  std::string opt = argv[i];
  if (opt.compare("-nohelp") == 0) i++;
  for (; i < argc - 1; i++) {
    opt = argv[i];
    i++;
    if (opt.compare("-sharpen") == 0) {
      opt = argv[i];
      if (to_float(opt)) {
        float sharpen_amount = stof(opt);
        if (sharpen_amount < 0 || sharpen_amount > 100)
          i = 0;
        else
          f = new FSharpen(sharpen_amount);
      }
      if (i <= 0) std::cout << "Sharpen was used incorrectly" << std::endl;
    } else if (opt.compare("-edge") == 0) {
      i--;
      f = new FEdgeDetect();
    } else if (opt.compare("-threshold") == 0) {
      opt = argv[i];
      if (to_float(opt)) {
        float threshold_amount = stof(opt);
        if (threshold_amount < 0 || threshold_amount > 1)
          i = 0;
        else
          f = new FThreshold(threshold_amount);
      }
      if (i <= 0) std::cout << "Threshold was used incorrectly" << std::endl;
    } else if (opt.compare("-quantize") == 0) {
      opt = argv[i];
      if (to_int(opt)) {
        int quantize_bins = stoi(opt);
        if (quantize_bins < 0 || quantize_bins > 256)
          i = 0;
        else
          f = new FQuantize(quantize_bins);
      }
      if (i <= 0) std::cout << "Quantize was used incorrectly" << std::endl;
    } else if (opt.compare("-blur") == 0) {
      opt = argv[i];
      if (to_float(opt)) {
        float blur_amount = stof(opt);
        if (blur_amount < 0 || blur_amount > 20)
          i = 0;
        else
          f = new FBlur(blur_amount);
      }
      if (i <= 0) std::cout << "Blur was used incorrectly" << std::endl;
    } else if (opt.compare("-saturate") == 0) {
      opt = argv[i];
      if (to_float(opt)) {
        float saturate_amount = stof(opt);
        if (saturate_amount < -10 || saturate_amount > 10)
          i = 0;
        else
          f = new FSaturate(saturate_amount);
      }
      if (i <= 0) std::cout << "Saturate was used incorrectly" << std::endl;
    } else if (opt.compare("-channel") == 0) {
      float red, green, blue;
      opt = argv[i];
      if (to_float(opt))
        red = stof(opt);
      else
        i = 0;
      i++;
      opt = argv[i];
      if (to_float(opt))
        green = stof(opt);
      else
        i = 0;
      i++;
      opt = argv[i];
      if (to_float(opt))
        blue = stof(opt);
      else
        i = 0;
      if (i > 0) {
        if (red < 0 || red > 10
            || green < 0 || green > 10
            || blue < 0 || blue > 10) i = 0;
        else
          f = new FChannels(red, green, blue);
      }
      if (i <= 0) std::cout << "Channels was used incorrectly" << std::endl;
    } else {
      delete_filters();
      return false;
    }
    filters_.push_back(f);
  }
  return true;
}

void MIAFilterManager::delete_filters(void) {
  std::vector<Filter*>::iterator it;
  for (it = filters_.begin(); it != filters_.end(); it++) {
    delete (*it);
  }
  filters_.clear();
}

void MIAFilterManager::CompareImages(PixelBuffer *buf1,
                                     PixelBuffer *buf2) {
  int buf_w = buf1->width();
  int buf_h = buf1->height();
  if (buf_h != buf2->height() || buf_w != buf2->width()) {
    std::cout << "0\n";
    return;
  }

  ColorData px1;
  ColorData px2;

  float red, green, blue, alpha;

  for (int i = 0; i < buf_w; i++) {
    for (int j = 0; j < buf_h; j++) {
      px1 = buf1->get_pixel(i, j);
      px2 = buf2->get_pixel(i, j);
      red = px1.red() - px2.red();
      green = px1.green() - px2.green();
      blue = px1.blue() - px2.blue();
      alpha = px1.alpha() - px2.alpha();
      if (red || green || blue || alpha) {
        std::cout << "0\n";
        return;
      }
    }
  }
  std::cout << "1\n";
}

GLUI_Panel* MIAFilterManager::InitGlui(const GLUI *const glui,
                                       void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);
    AddBlurToGLUI(filter_panel, s_gluicallback);

    new GLUI_Column(filter_panel, true);
    /// AddSaturationToGLUI(filter_panel, s_gluicallback);
    {
      GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Grayscale");

      new GLUI_Button(satur_panel, "Apply",
      UICtrl::UI_APPLY_SATURATE,
      s_gluicallback);
    }
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
  }

  return filter_panel;
} /** MIAFilterManager::InitGlui() */

}  /** namespace image_tools */
