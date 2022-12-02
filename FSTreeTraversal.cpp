/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for FSTree.h. This is the one I'm working on.
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


//While loop to find and print each path ADD BETTER DOCUMENTATION
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

