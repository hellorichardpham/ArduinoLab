// ----------------------------------------------------------------------------
// ConstantVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANT_VARIABLE_H
#define CONSTANT_VARIABLE_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR__
#include "Flash.h"

// Use these macros to define your constant data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value)                \
  static const char name##_flash[] PROGMEM = value; \
  ConstantString name(name##_flash);

class ConstantString : public _FLASH_STRING
{
public:
  ConstantString(const char *arr) : _FLASH_STRING(arr){};
};

#else

// Use these macros to define your constant data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value)            \
  static const char name##_const[] = value;     \
  ConstantString name(name##_const);

class ConstantString
{
public:
  ConstantString(const char *arr) : str_(arr){};
  size_t length() const;
  char *copy(char *to, int size = -1, int offset = 0) const;
  char operator[](int index) const;
  void print(Print &stream) const;
private:
  const char *str_;
};
#endif

inline Print &operator <<(Print &stream, const ConstantString &printable)
{
  printable.print(stream);
  return stream;
}

inline bool operator==(const ConstantString& lhs, const ConstantString& rhs)
{
  char lhs_char_array[lhs.length() + 1];
  lhs.copy(lhs_char_array);
  char rhs_char_array[rhs.length() + 1];
  rhs.copy(rhs_char_array);
  return strcmp(lhs_char_array,rhs_char_array) == 0;
}

inline bool operator!=(const ConstantString& lhs, const ConstantString& rhs)
{
  return !(lhs == rhs);
}

inline bool operator==(const ConstantString& lhs, const char * rhs)
{
  char lhs_char_array[lhs.length() + 1];
  lhs.copy(lhs_char_array);
  return strcmp(lhs_char_array,rhs) == 0;
}

inline bool operator!=(const ConstantString& lhs, const char * rhs)
{
  return !(lhs == rhs);
}

inline bool operator==(const char * lhs, const ConstantString& rhs)
{
  return rhs == lhs;
}

inline bool operator!=(const char * lhs, const ConstantString& rhs)
{
  return !(lhs == rhs);
}

inline bool operator==(const ConstantString& lhs, const String& rhs)
{
  return lhs == rhs.c_str();
}

inline bool operator!=(const ConstantString& lhs, const String& rhs)
{
  return !(lhs == rhs);
}

inline bool operator==(const String& lhs, const ConstantString& rhs)
{
  return rhs == lhs;
}

inline bool operator!=(const String& lhs, const ConstantString& rhs)
{
  return !(lhs == rhs);
}
#endif
