all: ZanbarBone80.cpp

ZanbarBone80.cpp:
	./FilesToFunctions.sh
	./CheckFiles.sh

clean:
	rm -f $(ls {*.cpp,*.h} | egrep -v "^getfile.(h|cpp)$")
