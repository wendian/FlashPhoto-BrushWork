/*******************************************************************************
 * Name            : f_edge_detect.h
 * Project         : image_tools
 * Module          : Edge Detect Filter
 * Description     : Header file for Edge Detect Filter subclass
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/10/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_DETECT_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_DETECT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "lib/libimgtools/src/include/filter.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implements an edge filter using an convoluyion based filter that uses
 * a kernel to detect edges.
 *
 */
class FEdgeDetect : public Filter {
 public:
  FEdgeDetect(void);

 private:
  Kernel *MakeKernel(void);
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_F_EDGE_DETECT_H_
