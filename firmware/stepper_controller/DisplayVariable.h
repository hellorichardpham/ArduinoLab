// ----------------------------------------------------------------------------
// DisplayVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_DISPLAY_VARIABLE_H_
#define _STANDALONE_DISPLAY_VARIABLE_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "ConstantVariable.h"
#include "DisplayElement.h"


#define BASE_DEC 10
#define BASE_BIN 2
#define BASE_HEX 16
#define BASE_OCT 8


namespace Standalone
{
class DisplayVariable : public DisplayElement
{
public:
  static const uint8_t DISPLAY_WIDTH_DEFAULT_DEC=6;
  static const uint8_t DISPLAY_WIDTH_DEFAULT_BIN=15;
  static const uint8_t DISPLAY_WIDTH_DEFAULT_HEX=4;
  static const uint8_t DISPLAY_WIDTH_DEFAULT_OCT=5;

  DisplayVariable();
  virtual void setValue(long value);
  long getValue();
  String getDisplayString();
  virtual void setConstantStringArray(const ConstantString string_array[],
                                      const uint8_t string_count);
  void trimDisplayWidth();
  void setBaseDec();
  void setBaseBin();
  void setBaseHex();
  void setBaseOct();
  uint8_t getBase();
private:
  long value_;
  uint8_t base_;
  const ConstantString *string_array_;
  uint8_t string_count_;
};
}
#endif
