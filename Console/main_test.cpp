// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#define BOOST_TEST_DYN_LINK // Defines a main function

#define BOOST_TEST_MODULE test_city_of_thieves_console_module
#include <boost/test/unit_test.hpp>

#pragma GCC diagnostic pop
