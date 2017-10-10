#include "menudialog.h"

#include <cassert>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>

#include "ai.h"
#include "dice.h"
#include "getfile.h"
#include "terminal.h"
#include "helper.h"
#include "game.h"
#include "walkthrough.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_menu_dialog)
{
  const Character character(6+6,12+6,6+6,Item::luck_potion);
  const int seed{42};
  Game game(seed,character);

  Terminal dialog;
  dialog.SetSilent(true);

  MenuDialog menu;
  menu.SetObserver(&dialog);
  menu.ShowAbout();
  menu.ShowHints();
  menu.ShowIntroduction();
  menu.ShowManual();
  menu.ShowTeaser();

}
#pragma GCC diagnostic pop
