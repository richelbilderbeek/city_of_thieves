all: console console_test

console: Files/ZanbarBone80.cpp Console/CityOfThievesConsole

console_test: Files/ZanbarBone80.cpp Console/CityOfThievesConsoleTest

Console/CityOfThievesConsole: Console/CityOfThievesConsole.pro
	cd Console && qmake -qt=qt5 CityOfThievesConsole.pro && $(MAKE) release

Console/CityOfThievesConsoleTest: Console/CityOfThievesConsoleTest.pro
	cd Console && qmake -qt=qt5 CityOfThievesConsoleTest.pro && $(MAKE) debug

Files/ZanbarBone80.cpp:
	cd Files && $(MAKE)

clean:
	cd Files && $(MAKE) clean
	cd Console && $(MAKE) clean

