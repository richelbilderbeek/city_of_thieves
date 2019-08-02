#!/bin/bash
GCOV_EXE=gcov

OBJ_FILES_PATH=.

if [ ! -d "$OBJ_FILES_PATH" ]
then
  echo "Object file path not found at "$OBJ_FILES_PATH
  exit 1
fi

for filename in `find . | egrep '\.cpp'`; do $GCOV_EXE -n -o $OBJ_FILES_PATH $filename > /dev/null; done