#include "character.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>

#include "dice.h"
#include "helper.h"
#include "observer.h"


// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_character)
{
  Character a(1,2,3,Item::luck_potion);
  Character b(a);
  assert(a==b);
}
#pragma GCC diagnostic pop
