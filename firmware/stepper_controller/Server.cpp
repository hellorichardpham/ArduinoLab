// ----------------------------------------------------------------------------
// Server.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Server.h"


namespace Standalone
{
void defaultCallback()
{
}
volatile bool Server::enc_btn_pressed_ = false;
uint8_t Server::frame_current_ = 0;
Server::Callback Server::callbacks_[constants::FRAMES_COUNT_MAX];

Server::Server(Configuration configuration) :
  display_(configuration.display_serial),
  encoder_(configuration.enc_b_pin,configuration.enc_a_pin),
  enc_btn_pin_(configuration.enc_btn_pin),
  enc_btn_int_(configuration.enc_btn_int),
  btn_pin_(configuration.btn_pin),
  btn_int_(configuration.btn_int),
  switch_pin_(configuration.switch_pin),
  switch_int_(configuration.switch_int),
  lights_pin_(configuration.lights_pin),
  update_period_(configuration.update_period)
{
  interactive_variable_index_ = -1;
  frame_var_ptr_ = NULL;
  inc_var_ptr_ = NULL;
  enc_value_prev_ = 0;
}

void Server::enable()
{
  enabled_ = true;
  display_.displayOn();
  display_.blinkingCursorOn();
}

void Server::disable()
{
  enabled_ = false;
  ledOff();
  display_.displayOff();
}

bool Server::update()
{
  if (!enabled_)
  {
    return false;
  }

  if (led_off_ && (digitalRead(lights_pin_) == LOW))
  {
    ledOn();
  }
  else if (!led_off_ && (digitalRead(lights_pin_) == HIGH))
  {
    ledOff();
  }

  unsigned long time_now = millis();
  if ((int)(time_now - time_last_update_) < update_period_)
  {
    return false;
  }

  time_last_update_ = time_now;
  Server::frame_current_ = frame_var_ptr_->getValue();

  // Update current interactive variable values
  if (interactive_variable_index_ >= 0)
  {
    InteractiveVariable *int_var_ptr = &(interactive_variables_[interactive_variable_index_]);
    bool interactive_variable_index_changed = false;
    if (Server::enc_btn_pressed_)
    {
      Server::enc_btn_pressed_ = false;
      int int_var_prev = interactive_variable_index_;
      do
      {
        interactive_variable_index_++;
        if (interactive_variable_index_ >= (int)interactive_variables_.size())
        {
          interactive_variable_index_ = 0;
        }
        int_var_ptr = &(interactive_variables_[interactive_variable_index_]);
      }
      while (!int_var_ptr->inFrame(Server::frame_current_));
      if (int_var_prev != interactive_variable_index_)
      {
        interactive_variable_index_changed = true;
      }
    }

    if (!int_var_ptr->checkValueDirty() && !interactive_variable_index_changed)
    {
      int32_t enc_value = encoder_.read();
      if (inc_var_ptr_ && (int_var_ptr != inc_var_ptr_) && (int_var_ptr != frame_var_ptr_))
      {
        if (inc_var_ptr_->inFrame(Server::frame_current_))
        {
          int8_t inc_exp = inc_var_ptr_->getValue();
          int inc_value = 1;
          for (int i=0; i<inc_exp; ++i)
          {
            inc_value *= 10;
          }
          enc_value = (enc_value - enc_value_prev_)*inc_value + enc_value_prev_;
          encoder_.write(enc_value);
        }
      }
      int_var_ptr->updateWithEncoderValue(enc_value);
      if (int_var_ptr == frame_var_ptr_)
      {
        int_var_ptr->trimDisplayWidth();
      }
      enc_value_prev_ = enc_value;
    }
    // updateWithEncoderValue may have dirtied value
    if (int_var_ptr->checkValueDirty() || interactive_variable_index_changed)
    {
      encoder_.write(int_var_ptr->getValue());
      enc_value_prev_ = encoder_.read();
      int_var_ptr->clearValueDirty();
      interactive_variable_index_changed = false;
    }
    int_var_ptr->executeUpdateCallback();
  }

  int frame_prev = Server::frame_current_;
  Server::frame_current_ = frame_var_ptr_->getValue();
  if (Server::frame_current_ != frame_prev)
  {
    display_.clearScreen();
    // Dirty all interactive_variables
    for (unsigned int i=0; i<interactive_variables_.size(); ++i)
    {
      interactive_variables_[i].setDisplayDirty();
    }

    // Dirty all display_variables
    for (unsigned int i=0; i<display_variables_.size(); ++i)
    {
      display_variables_[i].setDisplayDirty();
    }

    // Dirty all display_labels
    for (unsigned int i=0; i<display_labels_.size(); ++i)
    {
      display_labels_[i].setDisplayDirty();
    }
  }

  // Update all interactive_variables on display
  for (unsigned int i=0; i<interactive_variables_.size(); ++i)
  {
    interactive_variables_[i].updateOnDisplay(display_,Server::frame_current_);
  }

  // Update all display_variables on display
  for (unsigned int i=0; i<display_variables_.size(); ++i)
  {
    display_variables_[i].updateOnDisplay(display_,Server::frame_current_);
  }

  // Update all display_labels on display
  for (unsigned int i=0; i<display_labels_.size(); ++i)
  {
    display_labels_[i].updateOnDisplay(display_,Server::frame_current_);
  }

  // Place the cursor back on the current interactive variable
  if (interactive_variable_index_ >= 0)
  {
    InteractiveVariable &int_var = interactive_variables_[interactive_variable_index_];
    display_.setCursor(int_var.getDisplayPosition());
  }
  return true;
}

DisplayLabel& Server::createDisplayLabel()
{
  DisplayLabel display_label;
  display_labels_.push_back(display_label);
  return display_labels_.back();
}

DisplayVariable& Server::createDisplayVariable()
{
  DisplayVariable display_var;
  display_variables_.push_back(display_var);
  return display_variables_.back();
}

InteractiveVariable& Server::createInteractiveVariable()
{
  InteractiveVariable int_var;
  interactive_variables_.push_back(int_var);
  if (interactive_variable_index_ < 0)
  {
    interactive_variable_index_ = 0;
  }
  return interactive_variables_.back();
}

InteractiveVariable& Server::createIncrementVariable(int width_max)
{
  if (!inc_var_ptr_)
  {
    InteractiveVariable& inc_var = createInteractiveVariable();
    inc_var_ptr_ = &inc_var;
  }
  if (width_max < 1)
  {
    width_max = 1;
  }
  else if (width_max > (constants::INC_STRING_COUNT - 1))
  {
    width_max = constants::INC_STRING_COUNT - 1;
  }
  inc_var_ptr_->setConstantStringArray(constants::increment_array,constants::INC_STRING_COUNT);
  inc_var_ptr_->setRange(0,width_max-1);
  inc_var_ptr_->setDisplayWidth(width_max);
  inc_var_ptr_->setValue(0);
  return *inc_var_ptr_;
}

void Server::attachCallbackToFrame(Callback callback, uint8_t frame)
{
  if (frame < constants::FRAMES_COUNT_MAX)
  {
    Server::callbacks_[frame] = callback;
  }
}

void Server::executeCurrentFrameCallback()
{
  (*Server::callbacks_[Server::frame_current_])();
}

void Server::encBtnIsr()
{
  Server::enc_btn_pressed_ = true;
}

void Server::btnIsr()
{
  (*Server::callbacks_[Server::frame_current_])();
}

void Server::switchIsr()
{
  (*Server::callbacks_[Server::frame_current_])();
}

void Server::ledOn()
{
  display_.setBrightnessDefault();
  led_off_ = false;
}

void Server::ledOff()
{
  display_.setBrightness(0);
  led_off_ = true;
}
}
