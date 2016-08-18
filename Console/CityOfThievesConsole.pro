INCLUDEPATH += ../Classes

win32 {
  QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror -std=c++1y
}

linux {
  QMAKE_CXX = g++-4.9
  QMAKE_CC = gcc-4.9
  QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror -std=c++14
}

# No use of QT, as the Nintendo DS does not support Qt
QT -= core gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

include(../Classes/CityOfThievesConsole.pri)
include(../Files/Files.pri)

SOURCES += main.cpp
