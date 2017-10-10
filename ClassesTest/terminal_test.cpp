#include "terminal.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "chapter.h"
#include "game.h"
#include "getfile.h"
#include "helper.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_terminal)
{
  Terminal t;
  t.SetSilent(true);
  t.ShowText(GetFile("Changelog"));
}
#pragma GCC diagnostic pop
