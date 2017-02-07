/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Description     : Header file for Tool base, includes the mask
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes

 ******************************************************************************/

#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/applyfunc.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * Tool is the abstract class that holds the mask for all the tools
 **/

class Tool {
 public:
  Tool(void);
  virtual ~Tool(void);  // All tools will use this destructor,
                        // Although it is virtual it won't be overwritten

  float **getMask(void);

  void apply(ColorData tool_color, int x, int y, PixelBuffer *canvas);

 protected:
  float **mask_;
  virtual void InitMask(void) = 0;
  // The mask will only ever be set up once at initialization
  // Changes Shape and values based on selected tool

  void setApplyFunc(ApplyFunc *new_function);
  ApplyFunc * apply_function_ = 0;

  int mask_height_;
  int mask_width_;
};

}  // namespace image_tools

#endif  // INCLUDE_TOOL_H_
