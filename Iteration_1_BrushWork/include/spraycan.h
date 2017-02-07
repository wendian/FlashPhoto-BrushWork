/*******************************************************************************
 * Name            : spraycan.h
 * Project         : BrushWork
 * Description     : Header file for SprayCan
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_SPRAYCAN_H_
#define INCLUDE_SPRAYCAN_H_

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

class SprayCan : public Tool {
 public:
  SprayCan(void);
  // virtual ~SprayCan();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_SPRAYCAN_H_
