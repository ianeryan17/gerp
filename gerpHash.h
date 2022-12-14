/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the linker file for gerp.cpp and contains the declarations
 * of the gerpHash class.
 * 
 */

#ifndef _GERPHASH_H_
#define _GERPHASH_H_

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
#include <sstream>

using namespace std;

class GerpHash
{
public:
    // Constructor
    GerpHash();

    // Destructor
    ~GerpHash();

    struct word{
        string wordString;
        vector<int> lineLocation;
    };

    void addWordtoSense(string &lineContent, int &lineCounter, int &tracker);
    void addWordtoInsense(string &lineContent, int &lineCounter, int &tracker);
    void addToHash(word &element, int &size, vector<vector<word>> *vash);
    string stripNonAlphaNum(string &input);
    bool isAlphaChar(char &c);
    void expandSenseHash();
    void expandInsenseHash();
    string makeLowercase(string &s);
    bool mustExpand(int &words, int &bucketCount);

    vector<vector<word>> *senseHash;
    vector<vector<word>> *insenseHash;

    int senseSize;
    int insenseSize;
    int wordCount;
    

private:

};

#endif