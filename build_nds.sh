#!/bin/bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
./build_files.sh
cd Nds
./build_music.sh
make --silent
