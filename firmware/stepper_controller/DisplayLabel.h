// ----------------------------------------------------------------------------
// DisplayLabel.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_DISPLAY_LABEL_H_
#define _STANDALONE_DISPLAY_LABEL_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "ConstantVariable.h"
#include "DisplayElement.h"


namespace Standalone
{
class DisplayLabel : public DisplayElement
{
public:
  DisplayLabel();
  String getDisplayString();
  void setConstantString(const ConstantString &label);
private:
  const ConstantString *label_ptr_;
};
}
#endif
