// ----------------------------------------------------------------------------
// InteractiveVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "InteractiveVariable.h"


namespace Standalone
{
InteractiveVariable::InteractiveVariable()
{
  min_ = -10000;
  max_ = 10000;
  setBaseDec();
  value_dirty_ = true;
  update_callback_ = NULL;
}

void InteractiveVariable::setRange(const long min, const long max)
{
  if (min < max)
  {
    min_ = min;
    max_ = max;
  }
  else
  {
    min_ = max;
    max_ = min;
  }
  if (getValue() < min_)
  {
    setValue(min_);
  }
  else if (getValue() > max_)
  {
    setValue(max_);
  }
}

void InteractiveVariable::trimDisplayWidthUsingRange()
{
  uint8_t display_width = 1;
  if (min_ < 0)
  {
    ++display_width;
  }
  long max_temp = max_;
  uint8_t display_width_default;
  uint8_t base = getBase();
  switch (base)
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
  while ((max_temp/base > 0) && (display_width <= display_width_default))
  {
    ++display_width;
    max_temp /= base;
  }
  setDisplayWidth(display_width);
}

long InteractiveVariable::getMin()
{
  return min_;
}

long InteractiveVariable::getMax()
{
  return max_;
}

void InteractiveVariable::setValue(long value)
{
  DisplayVariable::setValue(wrapValue(value));
  value_dirty_ = true;
}

void InteractiveVariable::updateWithEncoderValue(long value)
{
  DisplayVariable::setValue(wrapValue(value));
}

bool InteractiveVariable::checkValueDirty()
{
  return value_dirty_;
}

void InteractiveVariable::clearValueDirty()
{
  value_dirty_ = false;
}

long InteractiveVariable::wrapValue(long value)
{
  if ((value >= min_) && (value <= max_))
  {
    return value;
  }
  else
  {
    value_dirty_ = true;
    unsigned long range = (max_ - min_) + 1;
    if (value < min_)
    {
      value += range*((min_ - value)/range + 1);
    }
    return min_ + (value - min_)%range;
  }
}

void InteractiveVariable::setConstantStringArray(const ConstantString string_array[],
                                                 const uint8_t string_count)
{
  DisplayVariable::setConstantStringArray(string_array,string_count);
  setRange(0,string_count-1);
}

void InteractiveVariable::attachUpdateCallback(Callback update_callback)
{
  update_callback_ = update_callback;
}

void InteractiveVariable::executeUpdateCallback()
{
  if (update_callback_)
  {
    (*update_callback_)();
  }
}
}
