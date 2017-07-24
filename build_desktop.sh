#!/bin/bash
./build_files.sh
cd Desktop
qmake -qt=qt5
make