# City Of Thieves

Branch |[![Travis CI logo](TravisCI.png)](https://travis-ci.com)
-------|------------------------------------------------------------------------------------------------------------------------------------------------
master |[![Build Status](https://travis-ci.com/richelbilderbeek/CityOfThieves.svg?branch=master)](https://travis-ci.com/richelbilderbeek/CityOfThieves)
develop|[![Build Status](https://travis-ci.com/richelbilderbeek/CityOfThieves.svg?branch=develop)](https://travis-ci.com/richelbilderbeek/CityOfThieves)

City Of Thieves is a text adventure game after the English gamebook with the same name by Ian Livingstone. 

 * [Wikipedia](https://en.wikipedia.org/wiki/City_of_Thieves_%28gamebook%29)

![Console version](Screenshots/CityOfThievesConsole_1_0.png)
![Desktop version](Screenshots/CityOfThievesDesktop_1_0.png)
![Nintendo DS version](Screenshots/CityOfThievesNds_1_0.jpg)
![Nintendo DS version on emulator](Screenshots/CityOfThievesNdsEmulator_1_0.png)

## Building

To build all:

```
make
```

### Console

```
make console
```

### Desktop

```
make desktop
```

## Running

Be sure to have already build the files.

Then open the correct Qt Creator project:

 * Console: `Console/CityOfThievesConsole.pro`
 * Console (test only): `Console/CityOfThievesConsoleTest.pro`
 * Desktop: `Desktop/CityOfThievesDesktop.pro`
 * NDS: `Nds/source/GameCityOfThievesNds.pro`

## Downloads

 * [Windows executable](http://richelbilderbeek.nl/CityOfThievesExe.zip)
 * [Arch Linux AUR package](https://aur.archlinux.org/packages/cityofthieves-cli/) (Console version only for the moment)
 * [NDS](http://richelbilderbeek.nl/CityOfThievesNds.zip)
 * Download the Singularity image:

```
singularity pull library://richelbilderbeek/default/city_of_thieves 
```

## Video

 * General gameplay: [YouTube](https://youtu.be/0QeDhZQGPFo) [download (.ogv)](http://richelbilderbeek.nl/city_of_thieves.ogv)

## I want to help!

Great!

There is need for some testing and spelling corrections. Create a new Issue or email @richelbilderbeek.

## What are all those files in the folder `Files`?

The `.txt` files contain the story of 'City Of Thieves'. 
These are converted to C++ headers and source files by the `FilesToFunctions.sh` scripts. 
This was needed, because NitroFS (as part of libnds, as part of DevKitPro) does not support a filesystem on the NDS hardware.

## Contributors

 * Richel Bilderbeek: lead developer
 * Jeroen Niemandal: added autofight
 * Carmen IJsebaart: testing
 * Greg Fivash: testing
 * Sander van Kasteel: [Arch linux package maintainer](https://aur.archlinux.org/packages/cityofthieves-cli/), bug reporting

## External links

 * [libnds_example_1](https://github.com/richelbilderbeek/libnds_example_1): minimal NDS example
 * [libnds_example_2](https://github.com/richelbilderbeek/libnds_example_2): minimal NDS example with Madmax audio
 * [Richel Bilderbeek's games](https://github.com/richelbilderbeek/Games)
 * [Singularity scriptlet for City of Thieves](https://github.com/richelbilderbeek/singularity_example_6)

