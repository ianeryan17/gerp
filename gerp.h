/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the linker file for gerp.cpp.
 * 
 */

#ifndef _GERP_H_
#define _GERP_H_

#include "DirNode.h"
#include "FSTree.h"
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <cassert>

#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Gerp
{
public:
    // Constructor
    Gerp();

    // Gerp Functions
    void determineQuery(string query);

    // for testing
    void makeIndex(DirNode* rootNode, string dirName);
    void insert(string key);
    void search(string query);
    string stripNonAlphaNum(string input);
    bool isAlphaChar(char c);

    void makeGerpFile(string fileName, string path);
    void open_or_die(ifstream &stream, string fileName);

private:
    struct word{
        string wordString;
        vector<int> lineLocation;
    };

    struct gerpFile{
        string filePath;
        string fileName;
        vector<string> content;
        vector<vector<word>> senseHash;
        vector<vector<word>> insenseHash;
    };

    void addToHash(gerpFile file, word element, int wordCount);

    // void makeIndex(DirNode* rootNode, string dirName);
    // void insert(string key);
    // void search(string query);
    // string stripNonAlphaNum(string input);
    // bool isAlphaChar(char c);

    // void makeGerp(string fileName, string path);
    // void open_or_die(streamtype &stream, string fileName);


    // string filePath;
    // string fileName;
    // vector<string> content;
    // vector<vector<word>> senseHash;
    // vector<vector<word>> insenseHash;
};

#endif