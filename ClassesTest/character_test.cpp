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
#include "skill.h"
#include "luck.h"
#include "playercondition.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_character)
{
  const Character a(1,2,3,Item::luck_potion);
  const Character b(a);
  assert(a==b);
  BOOST_CHECK(HasItem(a, Item::shield));
  BOOST_CHECK(HasItem(a, Item::carralifs_sword));
  BOOST_CHECK(!HasItem(a, Item::chainmail_coat));
  BOOST_CHECK(
       HasItem(a, Item::dexterity_potion)
    || HasItem(a, Item::luck_potion)
    || HasItem(a, Item::stamina_potion)
  );
}

BOOST_AUTO_TEST_CASE(character_operator_minus)
{
  const int skill{GetBestInitialSkill()};
  const int luck{GetBestInitialLuck()};
  const int condition{GetBestInitialCondition()};
  const Item initial_item{Item::luck_potion};
  const bool auto_attack{true};
  const Character a(skill, condition, luck, initial_item, auto_attack);
  const Character b(skill, condition, luck, initial_item, auto_attack);
  assert(a == b);
  //const Character delta{b - a};
  //assert(delta.GetInitialCondition() == 0);
  //assert(delta.GetInitialLuck() == 0);
  //assert(delta.GetInitialSkill() == 0);
}

BOOST_AUTO_TEST_CASE(TestGetBestCharacter)
{
  // Best character has highest stats
  {
    const Character c{GetBestCharacter()};
    assert(c.GetInitialCondition() == 12);
    assert(c.GetInitialLuck() == 6 + 6);
    assert(c.GetInitialSkill() == 3 + 6);
  }

  // Character starts with a potion
  {
    const Character c{GetBestCharacter(Item::stamina_potion)};
    assert(HasItem(c, Item::stamina_potion));
  }
  // Character starts with an auto-fight
  {
    const bool auto_attack{true};
    const Character c{GetBestCharacter(Item::dexterity_potion, auto_attack)};
    assert(c.GetAutoAttack() == auto_attack);
  }
}

#pragma GCC diagnostic pop
