/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Sun Oct 2 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include <deque>
#include <stack>
#include "include/ui_ctrl.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
  undo_btn_(nullptr),
  redo_btn_(nullptr),
  undo_limit_(100),
  current_size_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(false);
}

void StateManager::UndoOperation(PixelBuffer *buffer) {
  std::cout << "Undoing..." << std::endl;
  /// only way to enable redo is to first click undo
  redo_toggle(true);

  /// Put curent state in the redo stack
  redo_stack_.push(*buffer);

  /// Get most recent state from undo deque
  *buffer = undo_deq_.front();
  undo_deq_.pop_front();
  if (undo_deq_.empty())
    undo_toggle(false);
}

void StateManager::RedoOperation(PixelBuffer *buffer) {
  std::cout << "Redoing..." << std::endl;
  /// Clicking redo means you can "undo the redo"
  undo_toggle(true);

  /// Put curent state in the undo deque
  undo_deq_.push_front(*buffer);

  /// Apply to the main canvas
  *buffer = redo_stack_.top();

  /// Remvoe from the stack
  redo_stack_.pop();
  if (redo_stack_.empty())
    redo_toggle(false);
}

/// CALL THIS *BEFORE* ALL CHANGES
void StateManager::UpdateState(const PixelBuffer &buffer) {
  redo_toggle(false);
  /// If we have a redo history, delete it all
  while (!redo_stack_.empty()) {
    redo_stack_.pop();
    current_size_--;
  }

  /// If we are at our limit still, remove earliest state
  if (current_size_ == undo_limit_) {
    undo_deq_.pop_back();
    current_size_--;
  }

  /// Normal behavior, just push new state to top
  undo_deq_.push_front(buffer);
  current_size_++;
  undo_toggle(true);
}

void StateManager::ResetState(void) {
  undo_toggle(false);
  redo_toggle(false);
  current_size_ = 0;

  undo_deq_.clear();
  while (!redo_stack_.empty()) {
    redo_stack_.pop();
    current_size_--;
  }
}

}  /** namespace image_tools */
