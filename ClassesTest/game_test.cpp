#include "game.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include "ai.h"
#include "character.h"
#include "terminal.h"
#include "dice.h"
#include "helper.h"
#include "chapter.h"
#include "walkthrough.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_game_helper)
{
  Helper();
}

BOOST_AUTO_TEST_CASE(test_game_create_chapter)
{
  Chapter(1);
}

BOOST_AUTO_TEST_CASE(test_game_has_repeatable_rng)
{
  const int seed{123456};
  Dice::Get()->SetSeed(seed);

  Character character1(
    Dice::Get()->Throw(),
    Dice::Get()->Throw() + Dice::Get()->Throw(),
    Dice::Get()->Throw(),
    Item::luck_potion
  );

  const Game game1(seed,character1);

  Dice::Get()->SetSeed(seed);

  Character character2(
    Dice::Get()->Throw(),
    Dice::Get()->Throw() + Dice::Get()->Throw(),
    Dice::Get()->Throw(),
    Item::luck_potion
  );

  const Game game2(seed,character2);
  BOOST_CHECK(character1.GetChapters() == character2.GetChapters());
}

BOOST_AUTO_TEST_CASE(test_game_win)
{
  const int seed{2};
  //Use a maxed-out character
  const Character character(6,12,12,Item::luck_potion);
  const bool silent{true};
  Walkthrough walkthrough(seed,character,silent);
  walkthrough.Start();
}

