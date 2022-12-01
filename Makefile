###
### Makefile for gerp
###
### Author:  Ryo Shimada and Ian Ryan

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
MAKEFLAGS += -L 


##  This rule builds the treeTraversal executable
traverse: FSTreeTraversal.o main.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o treeTraversal main.o FSTreeTraversal.o DirNode.o FSTree.o
	
##	This rule builds FSTreeTraversal.o
FSTreeTraversal.o: FSTree.h FSTreeTraversal.cpp DirNode.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp DirNode.o FSTree.o

##	This rule builds main.o
main.o: main.cpp FSTree.h DirNode.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c main.cpp

provide:

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
