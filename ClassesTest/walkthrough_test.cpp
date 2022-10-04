#include "walkthrough.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(the_winning_route_has_a_final_character)
{
  const int seed{0};
  const Character character{GetBestCharacter()};
  const bool silent{false};
  const std::vector<int> route{GetWinningRoute()};
  Walkthrough w(seed, character,silent,route);
  const Character final{w.Run()};
  assert(final.GetChapters() != character.GetChapters());
  assert(!IsDead(final));
}

#pragma GCC diagnostic pop
