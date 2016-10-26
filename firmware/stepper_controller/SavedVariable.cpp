// ----------------------------------------------------------------------------
// SavedVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "SavedVariable.h"


size_t SavedVariable::s_eeprom_index = 0;

SavedVariable::SavedVariable()
{
}

#ifndef ARDUINO_SAM_DUE
void SavedVariable::setValueToDefault()
{
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  int ee = eeprom_index_;
  for (size_t i=0; i<size_; ++i)
  {
    if(EEPROM.read(ee) == *p)
    {
      ee++;
      p++;
    }
    else
    {
      EEPROM.write(ee++,*p++);
    }
  }
}

bool SavedVariable::valueIsDefault()
{
  const byte* p = (const byte *)(const void *)default_value_ptr_;
  int ee = eeprom_index_;
  for (size_t i=0; i<size_; ++i)
  {
    if(EEPROM.read(ee) == *p)
    {
      ee++;
      p++;
    }
    else
    {
      return false;
    }
  }
  return true;
}
#else
void SavedVariable::setValueToDefault()
{
}

bool SavedVariable::valueIsDefault()
{
  return true;
}
#endif

size_t SavedVariable::getSize()
{
  return size_;
}

size_t SavedVariable::getArrayLength()
{
  return array_length_;
}

size_t SavedVariable::getArrayElementSize()
{
  return array_element_size_;
}
