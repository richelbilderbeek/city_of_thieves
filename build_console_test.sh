#!/bin/bash
./build_files.sh
cd Console
qmake CityOfThievesConsoleTest.pro
make