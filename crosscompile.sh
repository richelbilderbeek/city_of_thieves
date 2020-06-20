#!/bin/sh
# Crosscompiles City Of Thieves to the Windows operating system

CONSOLE_PRO=CityOfThievesConsole.pro
DESKTOP_PRO=CityOfThievesDesktop.pro

cd Console
if [ ! -e $CONSOLE_PRO ]
then
  echo "ERROR: Cannot find "$CONSOLE_PRO
  exit
fi
i686-w64-mingw32.static-qmake-qt5 $CONSOLE_PRO
make
cd ..

cd Desktop
if [ ! -e $DESKTOP_PRO ]
then
  echo "ERROR: Cannot find "$DESKTOP_PRO
  exit
fi
i686-w64-mingw32.static-qmake-qt5 $DESKTOP_PRO
make
cd ..

CONSOLE_EXE=./Console/release/CityOfThievesConsole.exe
DESKTOP_EXE=./Desktop/release/CityOfThievesDesktop.exe

if [ ! -e $CONSOLE_EXE ]
then
  echo "ERROR: Cannot find "$CONSOLE_EXE
else
  echo "OK: Can find "$CONSOLE_EXE
fi


if [ ! -e $DESKTOP_EXE ]
then
  echo "ERROR: Cannot find "$DESKTOP_EXE
else
  echo "OK: Can find "$DESKTOP_EXE
fi


mv $CONSOLE_EXE CityOfThievesConsole.exe
mv $DESKTOP_EXE CityOfThievesDesktop.exe
