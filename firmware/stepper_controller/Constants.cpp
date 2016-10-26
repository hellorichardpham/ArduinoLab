// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"

namespace Standalone
{
namespace constants
{
CONSTANT_STRING(inc0,"1");
CONSTANT_STRING(inc1,"10");
CONSTANT_STRING(inc2,"100");
CONSTANT_STRING(inc3,"1000");
CONSTANT_STRING(inc4,"10000");
CONSTANT_STRING(inc5,"100000");
CONSTANT_STRING(inc6,"1000000");
const ConstantString increment_array[] =
  {
    inc0,
    inc1,
    inc2,
    inc3,
    inc4,
    inc5,
    inc6,
  };
}
}
