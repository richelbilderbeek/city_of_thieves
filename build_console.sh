#!/bin/bash
./build_files.sh
cd Console
qmake -qt=qt5 CityOfThievesConsole.pro
make --silent
