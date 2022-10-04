#include "route.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_get_winning_route)
{
  const auto r{GetWinningRoute()};
  assert(!r.empty());

}
#pragma GCC diagnostic pop
