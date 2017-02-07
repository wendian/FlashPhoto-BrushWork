/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Description     : Header file for Eraser
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

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

class Eraser : public Tool {
 public:
  Eraser(void);
  // virtual ~Eraser();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_ERASER_H_
