#include "dice.h"

#include <cassert>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_dice)
{
  //Check if all numbers are thrown within range
  {
    for (int i=1; i!=7; )
    {
      assert(Dice::Get());
      const int x{Dice::Get()->Throw()};
      assert(x >= 1 && x <= 6);
      if (x == i) ++i;
    }
  }
}
#pragma GCC diagnostic pop
