// ----------------------------------------------------------------------------
// DisplayLabel.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "DisplayLabel.h"


namespace Standalone
{
DisplayLabel::DisplayLabel()
{
  label_ptr_ = NULL;
  setDisplayWidth(0);
}

String DisplayLabel::getDisplayString()
{
  if (label_ptr_)
  {
    int label_length = label_ptr_->length();
    char label_char_array[label_length+1];
    label_ptr_->copy(label_char_array);
    return String(label_char_array);
  }
  else
  {
    return String("");
  }
}

void DisplayLabel::setConstantString(const ConstantString &label)
{
  label_ptr_ = &label;
  setDisplayWidth(label.length());
}
}
