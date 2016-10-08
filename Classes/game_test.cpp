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


// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_game)
{
  const bool verbose{false};
  if (verbose) { std::clog << __func__ << std::endl; }

  {
    Helper();
  }


  if (verbose) { std::clog << "Create a chapter" << std::endl; }
  {
    Chapter(1);
  }
  if (verbose) { std::clog << "Test if game runs identically twice with same RNG seed" << std::endl; }
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
    assert(character1.GetChapters() == character2.GetChapters());
  }
  if (verbose) { std::clog << "Can the game be won?" << std::endl; }
  {
    const int seed{0};
    //Use a maxed-out character
    const Character character(6,12,12,Item::luck_potion);
    Walkthrough walkthrough(seed,character);
    walkthrough.Start();
  }
}
#pragma GCC diagnostic pop
