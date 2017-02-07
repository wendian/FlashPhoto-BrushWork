/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Description     : Header file for Highlighter
 * Copyright       : Group C05
 * Creation Date   : 10/07/2016
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

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

class Highlighter : public Tool {
 public:
  Highlighter(void);
  // virtual ~Highlighter();

 private:
  void InitMask(void);
};

}  // namespace image_tools

#endif  // INCLUDE_HIGHLIGHTER_H_
