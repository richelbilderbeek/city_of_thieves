#include "routes.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_gate)
{
  const Routes r(1, 74);
  BOOST_CHECK_EQUAL(r.GetStartingChapter(), 1);
  BOOST_CHECK_EQUAL(r.GetFinalChapter(), 74);

}
#pragma GCC diagnostic pop
