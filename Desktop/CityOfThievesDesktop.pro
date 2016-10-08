
win32 {
  INCLUDEPATH += C:/Boost/include
  INCLUDEPATH += C:/Boost
  LIBS += C:/Boost/stage/lib/libboost_filesystem-mgw49-mt-1_59.a
  LIBS += C:/Boost/stage/lib/libboost_system-mgw49-mt-d-1_59.a

  # Using Qt and a resource file does not work with -Weffc++
  QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++1y
}

unix:!macx {
  QMAKE_CXX = g++-5
  QMAKE_LINK = g++-5
  QMAKE_CC = gcc-5
  QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14
  # Using Qt and a resource file does not work with -Weffc++
}

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
