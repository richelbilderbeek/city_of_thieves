all: console console_test

console: Files/ZanbarBone80.cpp CityOfThievesConsole
	make --silent

CityOfThievesConsole: Console/Makefile
	cd Console && $(MAKE)

Console/Makefile: Console/CityOfThievesConsole.pro
	cd Console && qmake -qt=qt5 CityOfThievesConsole.pro

console_test: Files/ZanbarBone80.cpp
	./build_console_test.sh

Files/ZanbarBone80.cpp:
	cd Files && $(MAKE)

clean:
	cd Files && $(MAKE) clean
	cd Console && $(MAKE) clean

