/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the implementation of gerp.h.
 */

#include "gerp.h"
#include "gerpHash.h"

using namespace std;

Gerp::Gerp(){
    content.resize(0);
    tracker = 0;
    command = "";
    query = "";
}

// Input: DirNode* rootNode, string dirName
// Output: nothing
// Purpose: This function traverses the FSTree reaching each file and creates
// a filePath string for each file it reaches.
void Gerp::makeIndex(DirNode* rootNode, string &dirName){
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
                //cout << dirName << "/" << currNode->getFile(j)<< endl;
                string pathString = dirName + "/" + currNode->getFile(j);
                makeGerpFile(pathString);
            }
        }
    }
}

// Input: string path
// Output: nothing
// Purpose: this function creates a gerpFile struct and scans in the line
// content of the files found through the given path, and adds the appropriate
// values to the variables in the gerpFile instance. This function also adds
// the scanned lines of the file found from the given path to both the insense
// and sense hashes.
void Gerp::makeGerpFile(string &path){
    ifstream instream;
    open_or_die(instream, path);
    gerpFile newGerp;
    newGerp.filePath = path;
    newGerp.startIndex = tracker;
    files.push_back(newGerp);
    string lineContent;
    int lineCounter = 0;
    while (getline(instream, lineContent)){
        //cerr << fileName << " at line [" << testCounter << "]: " << lineContent << endl;
        content.push_back(lineContent);
        gerpHash.addWordtoSense(lineContent, lineCounter, tracker);
        gerpHash.addWordtoInsense(lineContent, lineCounter, tracker);
        lineCounter++;
    }
    tracker += lineCounter;
    instream.close();
}


// Input: ifstream &stream and string fileName
// Output: nothing
// Purpose: this function opens a file if possible, and otherwise exits.
void Gerp::open_or_die(ifstream &stream, string fileName){
    stream.open(fileName);
    if (stream.peek() == ifstream::traits_type::eof()){
        //cerr << "Empty file detected" << endl;
        stream.close();
    }
    else if (stream.fail()) {
        cerr << "Cannot open file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }
}

// Input: ofstream &stream and string fileName
// Output: nothing
// Purpose: this function opens a file if possible, and otherwise exits.
void Gerp::open_or_die2(ofstream &stream, string fileName){
    stream.open(fileName);
    if (stream.fail()) {
        cerr << "Cannot open file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }
}

// Input: nothing
// Output: nothing
// Purpose: this function is responsible for running the command loop that
// takes in the query, returns only once the quit command is given.
void Gerp::determineQuery(string output){
    open_or_die2(outstream, output);
    bool quitTriggered = false;
    while (not quitTriggered){
        cout << "Query? ";
        cin >> command;
        if(not (command[0] == '@')){
            searchString(command);
        } 
        else if(command == "@i" or command == "@insensitive"){
            cin >> query;
            searchIString(query);
        }
        else if (command == "@f"){
            cin >> query;
            outstream.close();
            open_or_die2(outstream, query);
        } else if (command[1] = 'q'){
            quitTriggered = true;
        }
        command = "";
        query = "";
    }
    outstream.close();
    cout << "Goodbye! Thank you and have a nice day." << endl;
    return;
}

// Input: string query
// Output: nothing
// Purpose: this function takes in a given string and searches within the 
// senseHash for lines that match this query exactly, logging the results. 
void Gerp::searchString(string query){
    query = gerpHash.stripNonAlphaNum(query);
    int key = hash<string>{}(query);
    int size = gerpHash.senseSize;
    int index = abs(key % size);
    for(int i = 0; i < gerpHash.senseHash->at(index).size(); i++){
        GerpHash::word currWord = gerpHash.senseHash->at(index).at(i);
        if(currWord.wordString == query){
            for(int j = 0; j < currWord.lineLocation.size(); j++){
                int lineNum = currWord.lineLocation.at(j);
                gerpFile *file = getFile(lineNum);
                string s = "";
                string numbers = to_string(lineNum - file->startIndex + 1);
                s += file->filePath + ":" + numbers;
                s += ": " + content.at(lineNum) + '\n';
                //cout << s;
                outstream << s;
                //cerr << "content size: " << content.size() << endl;
            }
        }
    }
}

// Input: string query
// Output: nothing
// Purpose: this function takes in a given string and searches within the 
// insenseHash for lines that match this query, while not caring about case,
// and logs the results.
void Gerp::searchIString(string query){
    query = gerpHash.stripNonAlphaNum(query);
    query = gerpHash.makeLowercase(query);
    int key = hash<string>{}(query);
    int size = gerpHash.insenseSize;
    int index = abs(key % size);
    for(int i = 0; i < gerpHash.insenseHash->at(index).size(); i++){
        GerpHash::word currWord = gerpHash.insenseHash->at(index).at(i);
        if(currWord.wordString == query){
            for(int j = 0; j < currWord.lineLocation.size(); j++){
                int lineNum = currWord.lineLocation.at(j);
                gerpFile *file = getFile(lineNum);
                //cerr << "LINEnum: " << lineNum << endl;
                //cerr << "startIndex: " << file->startIndex << endl;
                // cout << file->filePath << ":"; 
                // cout << (lineNum - file->startIndex + 1) << ": ";
                // cout << content.at(lineNum) << endl;
                string s = "";
                string numbers = to_string(lineNum - file->startIndex + 1);
                s += file->filePath + ":" + numbers;
                s += ": " + content.at(lineNum) + '\n';
                //cout << s;
                outstream << s;
                //cerr << "content size: " << content.size() << endl;
            }
        }
    }
}

// Input: int lineNum
// Output: gerpFile pointer
// Purpose: this function takes in a given integer line number in the vector
// called content that holds all the lines from every file, and returns the
// pointer to the gerpFile that that this line number is from.
Gerp::gerpFile* Gerp::getFile(int lineNum){
    for(int i = 0; i < files.size(); i++){
        //cerr << "lineNumber !! " << lineNum << endl;
        //cerr << "stIND: " << files.at(i).startIndex << endl;
        if(lineNum < files.at(i).startIndex){
            //cerr << "filePath: " << files.at(i-1).filePath << endl;
            return &files.at(i-1);
        }
    }
    return &files.at(files.size()-1);
}