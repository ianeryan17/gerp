/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for FSTree.h. This is the one that is hooked up to GitHub.
 */

#include "FSTree.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void printPath(string pathString);

string createPath(string dirName, const DirNode* rootNode){
    int n = 0;
    DirNode currNode;
    currNode = *rootNode;
    string pathString = currNode.getName();
    cerr << "ps: " << pathString << endl;
    while((currNode.getName() != dirName) and (not currNode.hasSubDir())){
        currNode = *currNode.getSubDir(n++);
        if(dirName != currNode.getName()){
            pathString += "/" + currNode.getName();
        }
    }
    printPath(pathString);
    return pathString;
}

void printPath(string pathString){
    cout << "/" + pathString << endl;
}