/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Description     : Header file for Pen
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_PEN_H_
#define INCLUDE_PEN_H_

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

class Pen : public Tool {
 public:
  Pen(void);
  // virtual ~Pen();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_PEN_H_
