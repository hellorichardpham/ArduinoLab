// ----------------------------------------------------------------------------
// Server.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_SERVER_H_
#define _STANDALONE_SERVER_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Streaming.h"
#include "NewhavenDisplay.h"
#include "Encoder.h"
#include "Array.h"
#include "Vector.h"
#include "ConstantVariable.h"
#include "Constants.h"
#include "DisplayLabel.h"
#include "DisplayVariable.h"
#include "InteractiveVariable.h"


namespace Standalone
{
void defaultCallback();

struct Configuration
{
  HardwareSerial &display_serial;
  const int enc_a_pin;
  const int enc_b_pin;
  const int enc_btn_pin;
  const int enc_btn_int;
  const int btn_pin;
  const int btn_int;
  const int switch_pin;
  const int switch_int;
  const int lights_pin;
  const int update_period;
};

class Server
{
public:
  typedef void(*Callback)();
  Server(Configuration configuration);
  template <size_t FRAME_COUNT>
  void setup(const ConstantString (&frame_names)[FRAME_COUNT]);
  void enable();
  void disable();
  bool update();
  template <size_t MAX_SIZE>
  void setDisplayLabelStorage(DisplayLabel (&display_labels)[MAX_SIZE]);
  DisplayLabel& createDisplayLabel();
  template <size_t MAX_SIZE>
  void setDisplayVariableStorage(DisplayVariable (&display_variables)[MAX_SIZE]);
  DisplayVariable& createDisplayVariable();
  template <size_t MAX_SIZE>
  void setInteractiveVariableStorage(InteractiveVariable (&interactive_variables)[MAX_SIZE]);
  InteractiveVariable& createInteractiveVariable();
  InteractiveVariable& createIncrementVariable(int width_max);
  void attachCallbackToFrame(Callback callback, uint8_t frame);
  void executeCurrentFrameCallback();
private:
  NewhavenDisplay display_;
  Encoder encoder_;
  const int enc_btn_pin_;
  const int enc_btn_int_;
  const int btn_pin_;
  const int btn_int_;
  const int switch_pin_;
  const int switch_int_;
  const int lights_pin_;
  const int update_period_;
  bool enabled_;
  bool led_off_;
  unsigned long time_last_update_;
  uint8_t frame_count_;
  InteractiveVariable *frame_var_ptr_;
  Vector<DisplayLabel> display_labels_;
  Vector<DisplayVariable> display_variables_;
  Vector<InteractiveVariable> interactive_variables_;
  int interactive_variable_index_;
  InteractiveVariable *inc_var_ptr_;
  uint32_t enc_value_prev_;
  static const int FRAME_VAR_DISPLAY_POSITION = 0;
  static const int FRAME_VAR_DISPLAY_WIDTH = 1;
  static volatile bool enc_btn_pressed_;
  static void encBtnIsr();
  static void btnIsr();
  static void switchIsr();
  static Callback callbacks_[constants::FRAMES_COUNT_MAX];
  static uint8_t frame_current_;
  void ledOn();
  void ledOff();
};
}
#include "ServerDefinitions.h"

#endif
