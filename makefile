STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

obj/mySem.o: src/mySemaphore.h src/mySemaphore.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/mySem.o src/mySemaphore.cpp

obj/boat.o: src/boat.h src/boat.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/boat.o src/boat.cpp

obj/human.o: src/human.h src/human.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/human.o src/human.cpp

bin/island: obj/mySem.o obj/human.o obj/boat.o src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/island obj/mySem.o obj/human.o obj/boat.o src/main.cpp

.PHONY: doc run clean

run: bin/island
	./bin/island 7 9

doc:
	doxygen config
	cd latex && make

clean:
	rm -f obj/*.o
	rm -f bin/island
	rm -r -f bin
	rm -r -f obj
	rm -r -f html
	rm -r -f latex
