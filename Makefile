CXX:=g++
CXXFLAGS:=-Wall -Werror -Wextra -pedantic -std=c++17 -fopenmp
TESTFLAGS:=-Wall -std=c++17 -fopenmp
RELEASEFLAGS:=-O3
DEBUGFLAGS:=-g
SOURCEDIR=src
TESTCASESDIR=testcases
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
APPNAME:=troons
TESTCASEFILE:= $(TESTCASESDIR)/generatedInput.in

.PHONY: all clean test generateTest quickTest compareTimingSeq1
all: submission

compareTimingSeq1: clean submission generateTest
	perf stat -o result/our_result.out -e cycles,instructions,cache-misses ./$(APPNAME) $(TESTCASEFILE)
	perf stat -o result/troons_seq1_result.out -e cycles,instructions,cache-misses ./troons_seq $(TESTCASEFILE)

quickTest: clean submission generateTest
	./$(APPNAME) $(TESTCASEFILE)

submission: main.o
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -o $(APPNAME) $^ $(shell find -name '*.o' ! -name 'main.o')

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -c $^ $(SOURCES)

clean:
	$(RM) *.o troons test generateTest

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -D DEBUG -o troons main.cpp $(SOURCES)

generateTest: lib/GenerateTest.cpp
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -o generateTest $^
	./generateTest 1000 1000 1000 > $(TESTCASEFILE)