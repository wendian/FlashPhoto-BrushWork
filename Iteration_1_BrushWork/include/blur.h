/*******************************************************************************
 * Name            : blur.h
 * Project         : BrushWork
 * Description     : Header file for Blur Tool
 * Copyright       : Group C05
 * Creation Date   : 10/14/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_BLUR_H_
#define INCLUDE_BLUR_H_

/*******************************************************************************
* Includes
******************************************************************************/

#include "include/tool.h"

/*******************************************************************************
* Namespaces
******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class Blur : public Tool {
 public:
  Blur(void);
  // virtual ~Blur();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_BLUR_H_
