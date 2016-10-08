#include "ai.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "chapter.h"
#include "dice.h"
#include "game.h"
#include "helper.h"
#include "option.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_ai)
{
  //See that payoffs increase
  if (1==2)
  {
    Ai ai;
    Character character(6+6,12+6,6+6,Item::luck_potion);
    character.SetChapter(2); //Make the Character have travelled a bit
    character.SetChapter(3); //Make the Character have travelled a bit
    const double a{ai.CalcFinalPayoff(character)};
    character.AddItem(Item::black_pearls);
    const double b{ai.CalcFinalPayoff(character)};
    assert(b > a);
    character.AddItem(Item::lotus_flower);
    const double c{ai.CalcFinalPayoff(character)};
    assert(c > b);
    character.AddItem(Item::hags_hair);
    const double d{ai.CalcFinalPayoff(character)};
    assert(d > c);
    character.AddItem(Item::tattoo);
    const double e{ai.CalcFinalPayoff(character)};
    assert(e > d);
    character.AddItem(Item::silver_arrow);
    const double f{ai.CalcFinalPayoff(character)};
    assert(f > e);
    character.SetChapter(400);
    const double g{ai.CalcFinalPayoff(character)};
    assert(g > f);
  }
  //Do one run
  {
    Ai ai;
    const Character character(6+6,12+6,6+6,Item::luck_potion);
    Game game(42,character);
    game.SetObserver(&ai);

    while (1)
    {
      game.DoChapter();
      if (game.HasLost() || game.HasWon()) break;
    }
    ai.SetFinalPayoff(ai.CalcFinalPayoff(game.GetCharacter()));
  }
}
#pragma GCC diagnostic pop
