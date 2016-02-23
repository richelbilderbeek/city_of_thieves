#!/bin/sh

CONSOLE_EXE=GameCityOfThievesConsole.exe
DESKTOP_EXE=GameCityOfThievesDesktop.exe
CONSOLE_NDS=./Nds/GameCityOfThieves.nds

if [ ! -e $CONSOLE_EXE ]
then
  ./crosscompiletowindows.sh
fi

if [ ! -e $CONSOLE_EXE ]
then
  echo "ERROR: Cannot find "$CONSOLE_EXE
  exit
fi

if [ ! -e $DESKTOP_EXE ]
then
  ./crosscompiletowindows.sh
fi

if [ ! -e $DESKTOP_EXE ]
then
  echo "ERROR: Cannot find "$DESKTOP_EXE
  exit
fi

if [ ! -e $CONSOLE_NDS ]
then
  cd Nds
  make
  cd ..
fi

if [ ! -e $CONSOLE_NDS ]
then
  echo "ERROR: Cannot find "$CONSOLE_NDS
  exit
fi

mkdir CityOfThieves

cp LICENSE ./CityOfThieves/LICENSE
cp $CONSOLE_EXE ./CityOfThieves/GameCityOfThievesConsole.exe
cp $DESKTOP_EXE ./CityOfThieves/GameCityOfThievesDesktop.exe
cp $CONSOLE_NDS ./CityOfThieves/GameCityOfThieves.nds

zip -9 -r GameCityOfThieves.zip CityOfThieves

rm -rf CityOfThieves