/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the linker file for gerp.cpp and contains the declarations
 * of the gerp class.
 * 
 */

#ifndef _GERP_H_
#define _GERP_H_

#include "gerpHash.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

class Gerp
{
public:
    // Constructor
    Gerp();

    struct gerpFile{
        string filePath;
        int startIndex;
    };

    // Gerp Functions
    void determineQuery();

    void searchString(string query);
    void searchIString(string query);

    // for testing
    vector<string> getContent();
    void makeIndex(DirNode* rootNode, string &dirName);
    void makeGerpFile(string &path);
    void open_or_die(ifstream &stream, string &fileName);
    void breakUpQuery(string s);


    gerpFile* getFile(int lineNum);

    GerpHash gerpHash;
    vector<string> content; // contains all the lines of every file
    int tracker;
    string query;
    string command;
    string output;

private:
    vector<gerpFile> files;
};

#endif