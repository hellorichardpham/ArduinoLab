// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_CONSTANTS_H_
#define _STANDALONE_CONSTANTS_H_
#include "ConstantVariable.h"


namespace Standalone
{
namespace constants
{
enum{FRAMES_COUNT_MAX=16};
enum{INC_STRING_COUNT=7};

extern ConstantString inc0;
extern ConstantString inc1;
extern ConstantString inc2;
extern ConstantString inc3;
extern ConstantString inc4;
extern ConstantString inc5;
extern ConstantString inc6;
extern const ConstantString increment_array[INC_STRING_COUNT];
}
}
#endif
