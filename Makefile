all: console console_test desktop

console: Files/ZanbarBone80.cpp Console/CityOfThievesConsole

console_test: Files/ZanbarBone80.cpp Console/CityOfThievesConsoleTest

desktop: Files/ZanbarBone80.cpp Desktop/CityOfThievesDesktop

nds: build/devkitpro-pacman.deb ../libnds/lib/libnds7.a
	cd Nds && ./build_music.sh
	export DEVKITPRO=/opt/devkitpro ; \
	  export DEVKITARM=/opt/devkitpro/devkitARM ; \
	  cd Nds && $(MAKE)

../libnds/lib/libnds7.a: ../libnds/Makefile
	export DEVKITPRO=/opt/devkitpro ; \
	  export DEVKITARM=/opt/devkitpro/devkitARM ; \
	  cd ../libnds && $(MAKE)

../libnds/Makefile:
	cd .. && git clone https://github.com/devkitPro/libnds.git

build/devkitpro-pacman.deb:
	mkdir -p build
	cd build && wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
	cd build && sudo dpkg -i devkitpro-pacman.deb
	sudo dkp-pacman -S nds-dev


Console/CityOfThievesConsole: Console/CityOfThievesConsole.pro
	cd Console && qmake -qt=qt5 CityOfThievesConsole.pro && $(MAKE) release

Console/CityOfThievesConsoleTest: Console/CityOfThievesConsoleTest.pro
	cd Console && qmake -qt=qt5 CityOfThievesConsoleTest.pro && $(MAKE) debug

Desktop/CityOfThievesDesktop: Desktop/CityOfThievesDesktop.pro
	cd Desktop && qmake -qt=qt5 CityOfThievesDesktop.pro && $(MAKE) release

Files/ZanbarBone80.cpp:
	cd Files && $(MAKE)

clean:
	cd Files && $(MAKE) clean
	cd Console && $(MAKE) clean
	cd Desktop && $(MAKE) clean

