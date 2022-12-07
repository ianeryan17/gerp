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

private:
    struct word{
        string wordString
        int lineLocation[];
    }

    void insert(string key);
    void search(string query);
    string stripNonAlphaNum(string input);
    bool isAlphaChar(char c);


    string filePath;
    string fileName;
    vector<string> content;
    vector<vector<word>> senseHash;
    vector<vector<word>> insenseHash;
};

#endif