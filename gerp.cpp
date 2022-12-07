/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the implementation of gerp.h.
 */

#include "gerp.h"

using namespace std;

Gerp::Gerp(){

}

// Input:
// Output:
// Purpose: 
void Gerp::makeIndex(DirNode* rootNode, string dirName){
    DirNode *currNode;
    DirNode *tempNode;
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
                makeIndex(tempNode, tempName);
            }
        } if (currNode->hasFiles()){
            int num2 = currNode->numFiles();
            for (int j = 0; j < num2; j++){
                cout << dirName << "/" << currNode->getFile(j)<< endl;
                string pathString = dirName + "/" + currNode->getFile(j);
                makeGerpFile(currNode->getFile(j), pathString);
            }
        }
    }
}

// Input:
// Output:
// Purpose: 
void Gerp::makeGerpFile(string fileName, string path){
    ifstream instream;
    //cerr << "file name: " << fileName << endl;
    //cerr << "path: " << path << endl;
    open_or_die(instream, path);
    gerpFile newGerp;
    newGerp.filePath = path;
    newGerp.fileName = fileName;
    vector<string> content;
    string lineContent;
    int testCounter = 0;
    while (getline(instream, lineContent)){
        //cerr << fileName << " at line [" << testCounter << "]: " << lineContent << endl;
        content.push_back(lineContent);
        testCounter++;
    }
}

// Input:
// Output:
// Purpose: 
void Gerp::open_or_die(ifstream &stream, string fileName){
    stream.open(fileName);
    
    if (stream.peek() == ifstream::traits_type::eof()){
        cerr << "Empty file detected" << endl;
        stream.close();
    }
    else if (stream.fail()) {
        // blank (all spaces) files incorrectly trigger this
        cerr << "Cannot open file:  " << fileName << endl;
        exit(EXIT_FAILURE);
    }
}

// Input:
// Output:
// Purpose: 
void Gerp::determineQuery(string query){

}