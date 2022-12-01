/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for FSTree.h.
 */

#include "FSTree.h"

using namespace std;

string createPath(string dirName, DirNode* rootNode){
    int n = 0;
    DirNode *currNode = new DirNode();
    string pathString = rootNode->getName();
    currNode = rootNode;
    while((currNode->getName() != dirName) and (currNode != nullptr)){
        currNode = currNode->getSubDir(n++);
        if(dirName != currNode->getName()){
            pathString += "/" + currNode->getName();
        }
    }
}

void printPath(string pathString){
    cout << "/" + pathString << endl;
}