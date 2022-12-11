###
### Makefile for gerp
###
### Author:  Ryo Shimada and Ian Ryan

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
MAKEFLAGS += -L 



##  This rule builds the gerpTest executable
gerpTest: gerp.o gerpTestMain.o DirNode.o FSTree.o gerpHash.o
	$(CXX) $(CXXFLAGS) -o gerpTest gerpTestMain.o gerpHash.o gerp.o DirNode.o FSTree.o

##  This rule builds the gerpHash.o
gerpHash.o: gerpHash.cpp gerp.h gerpHash.h
	$(CXX) $(CXXFLAGS) -c gerpHash.cpp

##	This rule builds gerp.o
gerp.o: gerp.cpp gerp.h gerpHash.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c gerp.cpp

##	This rule builds gerpTestMain.o
gerpTestMain.o: gerpTestMain.cpp gerp.h gerpHash.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c gerpTestMain.cpp

##  This rule builds the treeTraversal executable
traverse: FSTreeTraversal.o main.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o treeTraversal main.o FSTreeTraversal.o DirNode.o FSTree.o

##  This rule builds the stringMan executable
stringMan: main2.o stringProcessing.o
	$(CXX) $(CXXFLAGS) -o stringMan main2.o stringProcessing.o

##  This rule builds the stringProcessing.o
stringProcessing.o: stringProcessing.h stringProcessing.cpp
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp
	
##	This rule builds FSTreeTraversal.o
FSTreeTraversal.o: FSTree.h FSTreeTraversal.cpp DirNode.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp DirNode.o FSTree.o

##	This rule builds main.o
main.o: main.cpp FSTree.h DirNode.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c main.cpp

##	This rule builds main2.o
main2.o: main2.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c main2.cpp

provide:
	provide comp15 proj4_gerp_phase1 FSTreeTraversal.cpp \
		stringProcessing.h stringProcessing.cpp \
		README

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
