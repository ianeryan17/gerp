/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the implementation of gerpHash.h.
 */

#include "gerp.h"
#include "gerpHash.h"

using namespace std;

GerpHash::GerpHash(){
    senseHash = new vector<vector<word>>;
    insenseHash = new vector<vector<word>>;
    senseHash->resize(100000000);
    insenseHash->resize(10000);
    senseSize = 100000000;
    insenseSize = 10000;
    wordCount = 0;
}

GerpHash::~GerpHash(){
    delete senseHash;
    delete insenseHash;
}

//need big three if we want to make modular (for both hashes)
void GerpHash::expandSenseHash(){
    vector<vector<word>> *newHash = new vector<vector<word>>;
    int newSize = senseSize*2 + 1;
    newHash->resize(newSize);
    for(int i = 0; i < senseSize; i++){
        vector<word> currVec = senseHash->at(i);
        for(int j = 0; j < currVec.size(); j++){
            word currWord = currVec.at(j);
            addToHash(currWord, newSize, newHash);
        }
    }
    delete senseHash;
    senseSize = newSize;
    senseHash = newHash;
}

// Input: char c
// Output: boolean
// Purpose: this function takes a given input character and determines whether
// the character is an alphanumeric character or not, returning true if the
// chracter is an alphanumeric char.
bool GerpHash::isAlphaChar(char &c){
    if((int(c) <= 57 and int(c) >= 48) or (int(c) <= 90 and int(c) >= 65)){
        return true;
    } else if(int(c) <= 122 and int(c) >= 97){
        return true;
    } else {
        return false;
    }
}

// Input: string input
// Output: string output
// Purpose: this function removes all leading and trailing non-alphanumeric
// characters from the given input string.
string GerpHash::stripNonAlphaNum(string &input){
    string output = "";
    string temp = "";
    bool isOpen = false;
    int size = (int) input.size();
    for(int i = 0; i < size; i++){
        if(isAlphaChar(input[i])){
            if (isOpen){
                output += temp;
                temp = "";
                isOpen = false;
            }
            if((i < size - 1) and (not isAlphaChar(input[i+1]))){
                isOpen = true;
            } 
            output += input[i];
        } else if (isOpen and (not isAlphaChar(input[i]))){
            temp += input[i];
        }
    }
    return output;
}

// Input: string lineContent, int lineCounter, int tracker
// Output: nothing
// Purpose: this function
void GerpHash::addWord(string &lineContent, int &lineCounter, int &tracker){
    string newWordString;
    stringstream wordStream(lineContent);
    while (wordStream >> newWordString) {
        if(mustExpand(wordCount, senseSize)){
            cerr << "EXPANDING Sense hash" << endl;
            expandSenseHash();
        }
        word newWord;
        newWord.wordString = stripNonAlphaNum(newWordString);
        //cerr << "newWord: " << newWord.wordString << endl;
        newWord.lineLocation.push_back(lineCounter + tracker);
        addToHash(newWord, senseSize, senseHash);
        wordCount++;
        //cerr << "word count: " << wordCount << endl;
        //cerr << "sense size: " << senseSize << endl;
    }
}

bool GerpHash::mustExpand(int &words, int &bucketCount){
    float loadFactor = ((float) words)/((float) bucketCount);
    //cerr << "load Factor: " << loadFactor << endl;
    if(.75 < loadFactor){
        return true;
    }
    return false;
}

// Input: word element, int size
// Output: nothing
// Purpose: 
void GerpHash::addToHash(word &element, int &size, vector<vector<word>> *vecHash){
    int key = hash<string>{}(element.wordString);
    //cerr << "total size: " << size << endl;
    //cerr << "key: " << key << endl;
    int index = abs(key % size);
    //cerr << "index: " << index << endl;
    //cerr << "size: " << vecHash->at(index).size() << endl;
    //cerr << "vecHash addy3: " << vecHash << endl;
    if(vecHash->at(index).size() == 0){
        vecHash->at(index).push_back(element);
    } else {
        for(int i = 0; i < vecHash->at(index).size(); i++){
            int lineNum = element.lineLocation.back();
            if(vecHash->at(index).at(i).wordString == element.wordString){
                if(not (vecHash->at(index).at(i).lineLocation.back() == lineNum)){
                    vecHash->at(index).at(i).lineLocation.push_back(lineNum);
                }
            } else {
                vecHash->at(index).push_back(element);
            }
        }
    }
}