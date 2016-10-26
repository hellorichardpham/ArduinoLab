// ----------------------------------------------------------------------------
// ConstantVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ConstantVariable.h"

#ifdef __AVR__

#else

size_t ConstantString::length() const
{
  return strlen(str_);
}

char *ConstantString::copy(char *to, int size, int offset) const
{
  size_t len = length();
  // to must be >= (len + 1 - offset) bytes long, but cannot check
  if ((size == -1) && (offset >= 0) && (offset <= (int)len))
  {
    memmove(to, str_ + offset, len + 1 - offset);
    to[len - offset] = 0;
  }
  // to must be >= (size - offset) bytes long, but cannot check
  else if ((size <= (int)(len + 1)) && (offset >= 0) && (offset < size))
  {
    memmove(to, str_ + offset, size - offset);
    to[size - 1 - offset] = 0;
  }
  else
  {
    to[0] = 0;
  }
  return to;
}

char ConstantString::operator[](int index) const
{
  return str_[index];
}

void ConstantString::print(Print &stream) const
{
  stream.print(str_);
}

#endif
