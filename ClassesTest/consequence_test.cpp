#include "consequence.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(a_default_consequence_is)
{
  const Consequence a;
  const Consequence b;
  assert(a == b);
}


BOOST_AUTO_TEST_CASE(a_default_consequence_is_of_no_consequence)
{
  const Consequence c;
  assert(IsNoConsequence(c));
}
#pragma GCC diagnostic pop
