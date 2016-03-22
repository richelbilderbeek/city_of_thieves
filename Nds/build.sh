#!/bin/bash
#grit_exe=~/devkitPro/devkitARM/bin/grit
grit_exe=/opt/devkitpro/devkitARM/bin/grit

if [ ! -e $grit_exe ]
then
  echo "grit not found"
  echo "Tip: search it by using: "
  echo "  find /opt/devkitpro -name 'grit'
  echo "or:"
  echo "  find ~/ -name 'grit'
  echo "Then replace the executable by the found path"
fi

$grit_exe data/*.*
make

