#!/bin/bash
#
# Build the online (WebAssembly) version of City of Thieves
# using Emscripten.
#
# Usage, from the repository's root folder:
#
#   ./scripts/build_web.sh
#
# Requires 'emcc' (from Emscripten) to be in the PATH.
# Writes the game to 'docs/play/', so that the Zensical website
# can serve it.
set -euo pipefail

if [[ "$PWD" =~ scripts$ ]]; then
  echo "FATAL ERROR."
  echo "Please run the script from the project root."
  echo "Present working directory: $PWD"
  echo " "
  echo "Tip: like this"
  echo " "
  echo "  ./scripts/build_web.sh"
  echo " "
  exit 42
fi

output_folder="docs/play"
mkdir -p "${output_folder}"

# Convert the text files to C++ functions
(cd Files && ./FilesToFunctions.sh)

# Collect the source files
# shellcheck disable=SC2016
classes_sources=$(grep -o '\$\$PWD/[A-Za-z0-9_]*\.cpp' Classes/CityOfThievesConsole.pri | sed 's|\$\$PWD|Classes|')
# shellcheck disable=SC2016
files_sources=$(grep -o '\$\$PWD/[A-Za-z0-9_]*\.cpp' Files/Files.pri | sed 's|\$\$PWD|Files|')

# shellcheck disable=SC2086
emcc \
  -std=c++17 \
  -O2 \
  -DNDEBUG \
  -DGSL_UNENFORCED_ON_CONTRACT_VIOLATION \
  -IClasses \
  -IFiles \
  Web/main.cpp \
  ${classes_sources} \
  ${files_sources} \
  -sASYNCIFY \
  -sALLOW_MEMORY_GROWTH \
  -sMODULARIZE \
  -sEXPORT_NAME=createCityOfThieves \
  -sEXPORTED_FUNCTIONS=_main,_malloc,_free \
  -sEXPORTED_RUNTIME_METHODS=UTF8ToString,stringToUTF8,lengthBytesUTF8 \
  -o "${output_folder}/city_of_thieves.js"

cp Web/game.html "${output_folder}/game.html"

echo "Online version built in '${output_folder}'"
