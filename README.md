# City Of Thieves

[![Travis CI logo](TravisCI.png)](https://travis-ci.org)
![Whitespace](Whitespace.png)
[![Codecov logo](Codecov.png)](https://www.codecov.io)
[![gplv3](http://www.gnu.org/graphics/gplv3-88x31.png)](http://www.gnu.org/licenses/gpl.html)[![cc-by-sa](http://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)

[![Build Status](https://travis-ci.org/richelbilderbeek/CityOfThieves.svg?branch=master)](https://travis-ci.org/richelbilderbeek/CityOfThieves)
[![codecov.io](https://codecov.io/github/richelbilderbeek/CityOfThieves/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/CityOfThieves?branch=master)

City Of Thieves is a text adventure game after the English gamebook with the same name by Ian Livingstone. 

 * [Wikipedia](https://en.wikipedia.org/wiki/City_of_Thieves_%28gamebook%29)

![Console version](Screenshots/CityOfThievesConsole_1_0.png)
![Desktop version](Screenshots/CityOfThievesDesktop_1_0.png)
![Nintendo DS version](Screenshots/CityOfThievesNds_1_0.jpg)
![Nintendo DS version on emulator](Screenshots/CityOfThievesNdsEmulator_1_0.png)

## Downloading

 * [here](http://richelbilderbeek.nl/GameCityOfThieves.htm).

## Building

 * Console version: `cd Console`, `qmake`,`make`
 * Desktop version: `cd Desktop`, `qmake`,`make`
 * Nintendo DS version: `cd Nds`, `make`
 * Crosscompile to Windows: `./crosscompile.sh`

## I want to help!

Great!

There is need for some testing and spelling corrections. Create a new Issue or email @richelbilderbeek.

## What are all those files in the folder `Files`?

The `.txt` files contain the story of 'City Of Thieves'. 
These are converted to C++ headers and source files by the `FilesToFunctions.sh` scripts. 
This was needed, because NitroFS (as part of libnds, as part of DevKitPro) does not support a filesystem on the NDS hardware.

