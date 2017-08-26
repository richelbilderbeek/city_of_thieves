INCLUDEPATH += ../Classes
include(../Classes/CityOfThievesConsole.pri)
include(../Files/Files.pri)

SOURCES += main.cpp

# Debug and release mode
CONFIG += debug_and_release

# In release mode, define NDEBUG
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # gprof
  QMAKE_CXXFLAGS += -pg
  QMAKE_LFLAGS += -pg

  # GSL
  DEFINES += GSL_UNENFORCED_ON_CONTRACT_VIOLATION
}

# In debug mode, turn on gcov and UBSAN
CONFIG(debug, debug|release) {

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov

  # UBSAN
  QMAKE_CXXFLAGS += -fsanitize=undefined
  QMAKE_LFLAGS += -fsanitize=undefined
  LIBS += -lubsan

  # gprof
  QMAKE_CXXFLAGS += -pg
  QMAKE_LFLAGS += -pg

  # GSL
  #DEFINES += GSL_THROW_ON_CONTRACT_VIOLATION
  DEFINES += GSL_UNENFORCED_ON_CONTRACT_VIOLATION
}

# Qt
QT -= core gui widgets

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
#QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
#QMAKE_CXXFLAGS += -fext-numeric-literals

# Boost.Test
LIBS += -lboost_unit_test_framework

