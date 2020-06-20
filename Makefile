all: console console_test desktop

console: Files/ZanbarBone80.cpp Console/CityOfThievesConsole

console_test: Files/ZanbarBone80.cpp Console/CityOfThievesConsoleTest

desktop: Files/ZanbarBone80.cpp Desktop/CityOfThievesDesktop

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

