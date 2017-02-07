/*******************************************************************************
 * Name            : calligraphypen.h
 * Project         : BrushWork
 * Description     : Header file for CalligraphyPen
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_CALLIGRAPHYPEN_H_
#define INCLUDE_CALLIGRAPHYPEN_H_

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

class CalligraphyPen : public Tool {
 public:
  CalligraphyPen(void);
  // virtual ~CalligraphyPen();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_CALLIGRAPHYPEN_H_
