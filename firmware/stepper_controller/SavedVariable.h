// ----------------------------------------------------------------------------
// SavedVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SAVED_VARIABLE_H
#define SAVED_VARIABLE_H

#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif

#include "Arduino.h"
#include "Streaming.h"


class SavedVariable
{
public:
  SavedVariable();
  template<typename T>
  SavedVariable(const T & default_value);
  template<typename T>
  SavedVariable(const T default_value[],
                const size_t array_length);
  template<typename T>
  int getDefaultValue(T & value);
  template<typename T>
  int getDefaultElementValue(const size_t element_index, T & value);
  template<typename T>
  int setValue(const T &value);
  template<typename T>
  int setElementValue(const size_t element_index, const T & value);
  template<typename T>
  int getValue(T & value);
  template<typename T>
  int getElementValue(const size_t element_index, T & value);
  void setValueToDefault();
  bool valueIsDefault();
  template<typename T>
  bool setDefaultValue(const T & default_value);
  size_t getSize();
  size_t getArrayLength();
  size_t getArrayElementSize();
private:
  static size_t s_eeprom_index;
  size_t eeprom_index_;
  size_t size_;
  const void * default_value_ptr_;
  size_t array_length_;
  size_t array_element_size_;
};
#include "SavedVariableDefinitions.h"
#endif
