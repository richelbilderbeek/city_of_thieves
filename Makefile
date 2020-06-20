
console: Files/ZanbarBone80.cpp
	./build_console.sh

Files/ZanbarBone80.cpp:
	cd Files && $(MAKE) ; cd ..

clean:
	rm *.o
	cd Files && $(MAKE) clean ; cd ..

