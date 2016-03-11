# -Weffc++ does not go with apfloat, Qwt

# Use a new version
QMAKE_CXX = g++-4.9
QMAKE_CC = gcc-4.9

QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}


SOURCES += qtmain.cpp

include(../Classes/CityOfThievesConsole.pri)
include(../Files/Files.pri)
include(../QtClasses/CityOfThievesDesktop.pri)
