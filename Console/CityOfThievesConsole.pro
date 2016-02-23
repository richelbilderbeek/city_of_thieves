INCLUDEPATH += ../Classes

win32 {
  # Windows only
  message("Console application, built for Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
}

macx {
  # Mac only
  message("Console application, built for Mac")
  QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
  CONFIG +=c++11
}

unix:!macx{
  # Linux only
  message("Console application, built for Linux")
  QMAKE_CXXFLAGS += -Werror
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
}

cross_compile {
  # Crosscompile only
  message("Console application, cross-compiling from Linux to Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
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
