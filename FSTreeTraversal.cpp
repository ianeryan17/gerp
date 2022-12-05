/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for FSTree.h.
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
    FSTree tree(dir);
    DirNode* root = tree.getRoot();
    printAll(root, dir);

    return 0;
}

// Input: DirNode* rootNode and string dirName
// Output: nothing
// Purpose: this function recursively tranverses the FSTree of DirNodes
// and prints out each of the possible file paths under the given dirName.
void printAll(DirNode* rootNode, string dirName){
    DirNode *currNode = new DirNode();
    DirNode *tempNode = new DirNode();
    string tempName;
    currNode = rootNode;
    if (currNode->isEmpty()){
        cout << dirName << endl;
        return;	
    } else {
        if (currNode->hasSubDir()){
            int num = currNode->numSubDirs();
            for (int i = 0; i < num; i++){
                tempNode = currNode->getSubDir(i);
                tempName = dirName;
                tempName += "/" + tempNode->getName();
                printAll(tempNode, tempName);
            }
        } if (currNode->hasFiles()){
            int num2 = currNode->numFiles();
            for (int j = 0; j < num2; j++){
                cout << dirName << "/" << currNode->getFile(j)<< endl;
            }
        }
    }
}