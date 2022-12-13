/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the implementation of gerpHash.h.
 */

#include "gerp.h"
#include "gerpHash.h"
#include <bits/stdc++.h>

using namespace std;

GerpHash::GerpHash(){
    senseHash = new vector<vector<word>>;
    insenseHash = new vector<vector<word>>;
    // 100000000
    senseHash->resize(100000000);
    insenseHash->resize(100000000);
    senseSize = 100000000;
    insenseSize = 100000000;
    wordCount = 0;
}

GerpHash::~GerpHash(){
    delete senseHash;
    delete insenseHash;
}

// Input: nothing
// Output: nothing
// Purpose: this function expands the senseHash hash table so that it can
// hold more vector<word>.
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

//need big three if we want to make modular (for both hashes)
// Input: nothing
// Output: nothing
// Purpose: this function expands the insenseHash hash table so that it can
// hold more vector<word>.
void GerpHash::expandInsenseHash(){
    vector<vector<word>> *newHash = new vector<vector<word>>;
    int newSize = insenseSize*2 + 1;
    newHash->resize(newSize);
    for(int i = 0; i < insenseSize; i++){
        vector<word> currVec = insenseHash->at(i);
        for(int j = 0; j < currVec.size(); j++){
            word currWord = currVec.at(j);
            addToHash(currWord, newSize, newHash);
        }
    }
    delete insenseHash;
    insenseSize = newSize;
    insenseHash = newHash;
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
// Purpose: this function takes in the content of a given line and creates a
// new word to the senseHash, expanding the hash table if necessary. In this
// new word, this function also record the lines of where this word can be
// found.
void GerpHash::addWordtoSense(string &lineContent, int &line, int &tracker){
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
        newWord.lineLocation.push_back(line + tracker);
        // DEBUG
        // if (newWord.wordString == "we"){
        //     cerr << "tracker#: " << tracker << endl;
        //     cerr << "linecount# " << lineCounter << endl;
        // }
        addToHash(newWord, senseSize, senseHash);
        wordCount++;
        //cerr << "word count: " << wordCount << endl;
        //cerr << "sense size: " << senseSize << endl;
    }
}

// Input: string lineContent, int lineCounter, int tracker
// Output: nothing
// Purpose: this function takes in the content of a given line and creates a
// new word to the insenseHash, expanding the hash table if necessary. In this
// new word, this function also record the lines of where this word can be
// found.
void GerpHash::addWordtoInsense(string &lineContent, int &lineCounter, int &tracker){
    string newWordString;
    stringstream wordStream(lineContent);
    while (wordStream >> newWordString) {
        if(mustExpand(wordCount, insenseSize)){
            cerr << "EXPANDING insense hash" << endl;
            expandInsenseHash();
        }
        word newWord;
        newWordString = stripNonAlphaNum(newWordString);
        newWord.wordString = makeLowercase(newWordString);
        //cerr << "newWord: " << newWord.wordString << endl;
        newWord.lineLocation.push_back(lineCounter + tracker);
        // DEBUG
        // if (newWord.wordString == "we"){
        //     cerr << "tracker#: " << tracker << endl;
        //     cerr << "linecount# " << lineCounter << endl;
        // }
        addToHash(newWord, insenseSize, insenseHash);
        wordCount++;
        //cerr << "word count: " << wordCount << endl;
        //cerr << "sense size: " << senseSize << endl;
    }
}

// Input: string s
// Output: string s2
// Purpose: this function iterates through a given string and returns the
// lowercase version of this string.
string GerpHash::makeLowercase(string s){
    string s2;
    for (int i = 0; i < s.size(); i++){
        s2 += tolower(s[i]);
    }
    return s2;
}  

// Input: int &words, int &bucketCount
// Output: boolean
// Purpose: this function takes in the number of words and number of buckets
// and determines whether the hash function needs to expand or not.
bool GerpHash::mustExpand(int &words, int &bucketCount){
    float loadFactor = ((float) words)/((float) bucketCount);
    //cerr << "load Factor: " << loadFactor << endl;
    if(.75 < loadFactor){
        return true;
    }
    return false;
}

// Input: word element, int size, and vector<vector<word>> *vecHash
// Output: nothing
// Purpose: this function takes in the word, size, and pointer to the hash 
// table, and adds the given word to the hash table at the index that the
// hash function produces by using the string of the word as the key.
void GerpHash::addToHash(word &elmt, int &size, vector<vector<word>> *vash){
    int key = hash<string>{}(elmt.wordString);
    //cerr << "total size: " << size << endl;
    //cerr << "key: " << key << endl;
    int index = abs(key % size);
    //cerr << "index: " << index << endl;
    //cerr << "size: " << vecHash->at(index).size() << endl;
    //cerr << "vecHash addy3: " << vecHash << endl;
    if(vash->at(index).size() == 0){
        vash->at(index).push_back(elmt);
    } else {
        for(int i = 0; i < vash->at(index).size(); i++){
            int lineNum = elmt.lineLocation.back();
            // DEBUG
            if(vash->at(index).at(i).wordString == elmt.wordString){
                if(not (vash->at(index).at(i).lineLocation.back() == lineNum)){
                    vash->at(index).at(i).lineLocation.push_back(lineNum);
                }
            } else {
                vash->at(index).push_back(elmt);
            }
        }
    }
}