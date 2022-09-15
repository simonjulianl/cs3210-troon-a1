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
	$(RM) *.o troons test

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -D DEBUG -o troons main.cpp $(SOURCES)

test: tests/test.cpp tests/catch.hpp
	$(CXX) $(TESTFLAGS) -o test $^ $(SOURCES) && ./test