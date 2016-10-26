// ----------------------------------------------------------------------------
// DisplayVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "DisplayVariable.h"


namespace Standalone
{
DisplayVariable::DisplayVariable()
{
  value_ = 0;
  string_array_ = NULL;
  string_count_ = 0;
  setBaseDec();
}

void DisplayVariable::setValue(long value)
{
  value_ = value;
  setDisplayDirty();
}

void DisplayVariable::trimDisplayWidth()
{
  if ((string_count_ > 0) && (value_ < string_count_))
  {
    setDisplayWidth(string_array_[value_].length());
  }
  else
  {
    uint8_t display_width = 1;
    long value_temp = value_;
    if (value_temp < 0)
    {
      ++display_width;
      value_temp = abs(value_temp);
    }
    uint8_t display_width_default;
    switch (base_)
    {
      case BASE_DEC:
        display_width_default = DISPLAY_WIDTH_DEFAULT_DEC;
        break;
      case BASE_BIN:
        display_width_default = DISPLAY_WIDTH_DEFAULT_BIN;
        break;
      case BASE_HEX:
        display_width_default = DISPLAY_WIDTH_DEFAULT_HEX;
        break;
      case BASE_OCT:
        display_width_default = DISPLAY_WIDTH_DEFAULT_OCT;
        break;
      default:
        display_width_default = DISPLAY_WIDTH_DEFAULT_DEC;
    }
    while ((value_temp/base_ > 0) && (display_width <= display_width_default))
    {
      ++display_width;
      value_temp /= base_;
    }
    setDisplayWidth(display_width);
  }
}

long DisplayVariable::getValue()
{
  return value_;
}

String DisplayVariable::getDisplayString()
{
  if ((string_count_ > 0) && (value_ < string_count_))
  {
    char display_char_array[DISPLAY_WIDTH_MAX+1];
    string_array_[value_].copy(display_char_array);
    return String(display_char_array);
  }
  else
  {
    switch (base_)
    {
      case BASE_DEC:
        return String(value_);
        break;
      case BASE_BIN:
        return String(value_,BIN);
        break;
      case BASE_HEX:
        return String(value_,HEX);
        break;
      case BASE_OCT:
        return String(value_,OCT);
        break;
      default:
        return String(value_);
    }
  }
}

void DisplayVariable::setConstantStringArray(const ConstantString string_array[],
                                             const uint8_t string_count)
{
  string_array_ = string_array;
  string_count_ = string_count;
  uint8_t string_length_max = 0;
  for (int index=0; index<string_count; index++)
  {
    int string_length = string_array_[index].length();
    if (string_length > string_length_max)
    {
      string_length_max = string_length;
    }
  }
  if (string_length_max > 0)
  {
    setDisplayWidth(string_length_max);
  }
}

void DisplayVariable::setBaseDec()
{
  base_ = BASE_DEC;
  setDisplayWidth(DISPLAY_WIDTH_DEFAULT_DEC);
}

void DisplayVariable::setBaseBin()
{
  base_ = BASE_BIN;
  setDisplayWidth(DISPLAY_WIDTH_DEFAULT_BIN);
}

void DisplayVariable::setBaseHex()
{
  base_ = BASE_HEX;
  setDisplayWidth(DISPLAY_WIDTH_DEFAULT_HEX);
}

void DisplayVariable::setBaseOct()
{
  base_ = BASE_OCT;
  setDisplayWidth(DISPLAY_WIDTH_DEFAULT_OCT);
}

uint8_t DisplayVariable::getBase()
{
  return base_;
}
}
