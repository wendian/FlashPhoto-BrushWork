/*******************************************************************************
 * Name            : filter.h
 * Project         : image_tools
 * Module          : Filter
 * Description     : Header file for Filter base class
 * Copyright       : 2016 CSCI3081W Group 11. All rights reserved.
 * Creation Date   : 11/06/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/kernel.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for all filters
 *
 * A Filter describes an algorithm for producing a filtered pixel based on a
 * PixelBuffer and a set of coordinates in that PixelBuffer. A filter can
 * either be simple (without a kernel) or convolution (with a kernel) based.
 */
class Filter {
 public:
  Filter(void);
  virtual ~Filter(void);
 /**
   * @brief Apply a filter to a buffer
   *
   * Buffer is updated to point to a NEW PixelBuffer (i.e. in place modification
   * is not done)
   *
   * @param buffer The buffer to apply to
   */
  void FilterApply(PixelBuffer *buffer);

  /**
  * @brief Get the kernel associated with the filter
  * @return The kernel
  */
  Kernel *kernel(void) { return kernel_; }

 protected:
  /**
   * @brief Each filter needs a different kernel, they are made at different times
   */
  virtual Kernel *MakeKernel(void) { return nullptr; }

  /**
   * @brief Set the kernel associated with the filter
   */
  void kernel(Kernel *kernel) { kernel_ = kernel; }

  /**
   * @brief Sets the filter's complexity, should never be changed after init
   */
  void set_complex(int is_complex) { is_complex_ = is_complex; }

  /**
   * @brief validate colordata for invalid rgb values (negative or >1).
   * @return ColorData that does not have invalid rgb values.
   */
  ColorData validate_color(float red, float green, float blue, float alpha);

   /**
   * @brief Convultion filters apply kernels to pixels
   * @return A modified pixel
   */
  virtual ColorData ApplyKernel(int x, int y, const PixelBuffer &buffer);

   /**
    * @brief Simple filters do not require a kernel and are applied
    * directly to the each individual pixel.
    * @return A modified pixel
    */
  virtual ColorData SimpleModifyPixel(const ColorData &old_color)
    { return old_color; }

 private:
  /**
   * Applies the selected convolutional filter to the buffer using
   * a kernel
   */
  virtual void ConvoFilterApply(PixelBuffer *buffer);
  /**
   * @brief Applies the selected simple filter to the buffer without using
   * a kernel
   */
  virtual void SimpleFilterApply(PixelBuffer *buffer);

  /** 
   * @brief Usage of copy/move construction or assignment is disallowed 
   */
  Filter(const Filter& rhs) = delete;
  Filter& operator=(const Filter& rhs) = delete;

  /**
   * @brief Complex filters need a kernel, this pointer leads to it
   */
  Kernel *kernel_;

 /**
  * @brief indicates whether a selected filter is convolutional or
  * simple.
  * @return 0 for simple filter or 1 for Convultion filter
  */
  int is_complex_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_FILTER_H_
