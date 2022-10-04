#include "observer.h"

int GetDefaultNumberOfCharsPerLine() noexcept
{
#ifndef ARM9
  return 80;
#else
  return 32;
#endif
}
