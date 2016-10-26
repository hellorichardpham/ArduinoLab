// ----------------------------------------------------------------------------
// InteractiveVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_INTERACTIVE_VARIABLE_H_
#define _STANDALONE_INTERACTIVE_VARIABLE_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "DisplayVariable.h"

namespace Standalone
{
class InteractiveVariable : public DisplayVariable
{
public:
  typedef void(*Callback)();
  InteractiveVariable();
  void setRange(const long min, const long max);
  void trimDisplayWidthUsingRange();
  long getMin();
  long getMax();
  virtual void setValue(long value);
  virtual void setConstantStringArray(const ConstantString string_array[],
                                      const uint8_t string_count);
  void attachUpdateCallback(Callback callback);
private:
  long min_;
  long max_;
  bool value_dirty_;
  Callback update_callback_;
  void updateWithEncoderValue(long value);
  bool checkValueDirty();
  void clearValueDirty();
  long wrapValue(long value);
  void executeUpdateCallback();
  friend class Server;
};
}
#endif
