// ----------------------------------------------------------------------------
// ServerDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_SERVER_DEFINITIONS_H_
#define _STANDALONE_SERVER_DEFINITIONS_H_


namespace Standalone
{
template<size_t FRAME_COUNT>
void Server::setup(const ConstantString (&frame_names)[FRAME_COUNT])
{
  display_.setup();
  disable();
  time_last_update_ = millis();

  pinMode(enc_btn_pin_,INPUT);
  digitalWrite(enc_btn_pin_,HIGH);
  attachInterrupt(enc_btn_int_,encBtnIsr,FALLING);

  pinMode(btn_pin_,INPUT);
  digitalWrite(btn_pin_,HIGH);
  attachInterrupt(btn_int_,btnIsr,FALLING);

  pinMode(switch_pin_,INPUT);
  digitalWrite(switch_pin_,HIGH);
  attachInterrupt(switch_int_,switchIsr,FALLING);

  pinMode(lights_pin_,INPUT);

  frame_var_ptr_ = &(createInteractiveVariable());
  frame_var_ptr_->setDisplayPosition(FRAME_VAR_DISPLAY_POSITION);
  frame_var_ptr_->setDisplayWidth(FRAME_VAR_DISPLAY_WIDTH);
  frame_var_ptr_->addToAllFrames();

  for (uint8_t frame=0; frame < constants::FRAMES_COUNT_MAX; frame++)
  {
    Server::callbacks_[frame] = defaultCallback;
  }

  if (FRAME_COUNT > constants::FRAMES_COUNT_MAX)
  {
    frame_count_ = constants::FRAMES_COUNT_MAX;
  }
  else
  {
    frame_count_ = FRAME_COUNT;
  }
  frame_var_ptr_->setConstantStringArray(frame_names,frame_count_);
}

template<size_t MAX_SIZE>
void Server::setDisplayLabelStorage(DisplayLabel (&display_labels)[MAX_SIZE])
{
  display_labels_.setStorage(display_labels);
}

template<size_t MAX_SIZE>
void Server::setDisplayVariableStorage(DisplayVariable (&display_variables)[MAX_SIZE])
{
  display_variables_.setStorage(display_variables);
}

template<size_t MAX_SIZE>
void Server::setInteractiveVariableStorage(InteractiveVariable (&interactive_variables)[MAX_SIZE])
{
  interactive_variables_.setStorage(interactive_variables);
}
}

#endif
