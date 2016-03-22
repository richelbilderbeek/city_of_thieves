#!/bin/bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
make

if [ ! -e travis_qmake_gcc_cpp98_libnds.nds ]
then
  echo "Build failed, retry build with more info"
  make -d --debug=v
  return 1
fi

