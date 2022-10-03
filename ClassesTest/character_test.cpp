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
  const Character a(1,2,3,Item::luck_potion);
  const Character b(a);
  assert(a==b);
  BOOST_CHECK(a.HasItem(Item::shield));
  BOOST_CHECK(a.HasItem(Item::carralifs_sword));
  BOOST_CHECK(!a.HasItem(Item::chainmail_coat));
  BOOST_CHECK(
       a.HasItem(Item::dexterity_potion)
    || a.HasItem(Item::luck_potion)
    || a.HasItem(Item::stamina_potion)
  );
}
#pragma GCC diagnostic pop
