CXX=g++
CXXFLAGS:=-Wall -Werror -Wextra -pedantic -std=c++17 -fopenmp
TESTFLAGS:=-Wall -std=c++17 -fopenmp
RELEASEFLAGS:=-O3
DEBUGFLAGS:=-g
SOURCEDIR=src
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')

.PHONY: all clean test
all: submission

submission: main.o
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -o troons $^ $(shell find -name '*.o' ! -name 'main.o')

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -c $^ $(SOURCES)

clean:
	$(RM) *.o troons test generateTest

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -D DEBUG -o troons main.cpp $(SOURCES)

generateTest: 
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -o generateTest $^ src/GenerateTest.cpp
	./generateTest 17000 200000 100000 > testcases/generatedInput.in