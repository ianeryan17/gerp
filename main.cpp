/*
 * Ryo Shimada and Ian Ryan
 * 11/30/22
 * 
 * This file acts as the main for FSTreeTraversal.cpp.
 */

#include "FSTree.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>


using namespace std;

void printAll(DirNode* rootNode, string dirName);

int main(int argc, char *argv[]){
    string dir = argv[1];
    DirNode bar("Bar");
    DirNode emptyNode("empty");
    bar.addFile("x.cpp");
    bar.addFile("y.cpp");
    bar.addFile("z.cpp");
    DirNode foo("Foo");
    foo.addSubDirectory(&bar);
    foo.addSubDirectory(&emptyNode);
    foo.addFile("a.cpp");
    foo.addFile("b.cpp");
    foo.addFile("c.cpp");
    printAll(&foo, dir);

    return 0;
}