/*******************************************************************************
 * Name            : state_manager.h
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Header for IoHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STATE_MANAGER_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STATE_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <deque>
#include <stack>
#include "GL/glui.h"
#include "lib/libimgtools/src/include/ui_ctrl.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for simulation state in FlashPhoto.
 *
 * Simulation state is defined as the sequence of operations that comprises the
 * current canvas. An operation is defined as what happens during 1 click/drag
 * operation, or when 1 button on the control panel that affects the canvas is
 * clicked.
 *
 * A sequence of undos followed by some edits, followed by more undos will
 * FIRST undo the new edits, until you get back to the state before you made the
 * edits. You will not be able to go back any further.
 */
class StateManager {
 public:
  StateManager();
  ~StateManager() {}

  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

  /**
   * @brief Undoes the last operation applied to the canvas (not permanently; it
   * can still be re-done later)
   *
   */
  void UndoOperation(PixelBuffer *buffer);

  /**
   * @brief Re-does the last un-done operation applied to the canvas (not
   * permanently; it can be undone again later)
   *
   */
  void RedoOperation(PixelBuffer *buffer);

  /**
   * @brief Updates each time an undoable action is made, pushes onto the undo
   * queue and clears out the redo stack
   *
   */
  void UpdateState(const PixelBuffer &buffer);

  /**
   * @brief Call when next/prev is pressed in MIA, since undo and redo for a
   * previous image in sequence is meaningless
   */
  void ResetState(void);

 private:
  /**
   * @brief Turns redo button on and off
   */
  void redo_toggle(bool select) {
    UICtrl::button_toggle(redo_btn_, select);
  }
  /**
   * @briefTurns undo button on and off
   */
  void undo_toggle(bool select) {
    UICtrl::button_toggle(undo_btn_, select);
  }

  /**
   * @brief Copy/move assignment/construction disallowed 
   */
  StateManager(const StateManager &rhs) = delete;
  StateManager& operator=(const StateManager &rhs) = delete;

  /** data members */
  GLUI_Button *undo_btn_;
  GLUI_Button *redo_btn_;

  /**
   * @brief Number of undos possible to avoid stack overflow
   */
  const int undo_limit_;
  /**
   * @brief Number of states saved in both redo and undo stacks
   */
  int current_size_;

  /**
   * @brief Undo kept in a deque to let old states fall off
   */
  std::deque<PixelBuffer> undo_deq_;
  /**
   * @brief Redo in a stack because we only access states LIFO
   */
  std::stack<PixelBuffer> redo_stack_;
};

}  /** namespace image_tools */

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_STATE_MANAGER_H_
