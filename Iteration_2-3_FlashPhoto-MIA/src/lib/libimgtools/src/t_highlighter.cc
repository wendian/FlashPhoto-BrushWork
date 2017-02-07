/*******************************************************************************
 * Name            : t_highlighter.cc
 * Project         : FlashPhoto
 * Module          : Tool
 * Description     : Implementation of highlighter tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_highlighter.h"
#include <string>
#include "include/m_oval.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
THighlighter::THighlighter(void) {
    mask(new MOval(7.0, 0.4, 90, 0.3));
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData THighlighter::color_blend_math(
    float mask_pixel_amount,
    const ColorData& tool_color,
    const ColorData& current_color,
    const ColorData& background_color) {
  float L = current_color.luminance();
  float intensity = mask_pixel_amount*L;
  return tool_color*intensity + current_color*(1.0-intensity);
}

}  /** namespace image_tools */
