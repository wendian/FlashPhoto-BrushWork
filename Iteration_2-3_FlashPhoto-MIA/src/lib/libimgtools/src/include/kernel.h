/*******************************************************************************
 * Name            : Kernel.h
 * Project         : image_tools
 * Module          : Kernel
 * Description     : Header file for Kernel base class
 * Copyright       : 2016 CSCI3081W Group 11
 * Creation Date   : 11/06/16
 * Original Author : Wendi An
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for all mathematical kernels used for filtering
 *
 */
class Kernel {
 public:
  explicit Kernel(int length);
  Kernel(void);
  virtual ~Kernel(void);

  /**
   * @brief Get a handle on the underlying array of float values representing
   * the values in the kernel
   * @return The float array
   */
  float **float_array(void) { return kernel_array_; }

  /**
   * @brief Get the height of the kernel
   * @return Height
   */
  int length(void) const {return length_;}

  /**
   * @brief Get the value of the kernel at (x,y)
   */
  float get_value(int x, int y) const;

  /**
   * @brief Set the value of the kernel at (x,y)
   */
  void set_value(int x, int y, float v);

 private:
  /**
   * @brief Copy/move assignment/construction are disallowed
   */
  Kernel(const Kernel& rhs) = delete;
  Kernel& operator=(const Kernel& rhs) = delete;
  /**
   * @brief < number of pixel rows and cols available in the kernel
   */
  int length_;
  /**
   * @brief < max distance in pixels the kernel reaches from center
   */
  float radius_;
  /**
   * @brief Array of floats that actually represent the kernel
   */
  float ** kernel_array_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_KERNEL_H_
