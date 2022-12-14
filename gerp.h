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
    void runGerp(DirNode* rootNode, string &dir, string &output);
    void determineQuery(string &output);

private:
    void searchString(string &input);
    void searchIString(string &input);

    void makeIndex(DirNode* rootNode, string &dirName);
    void makeGerpFile(string &path);
    void open_or_die(ifstream &stream, string &fileName); 
    void open_or_die2(ofstream &stream, string &fileName);   
    gerpFile* getFile(int &lineNum);
    vector<gerpFile> files;
    GerpHash gerpHash;
    vector<string> content;
    int tracker;
    string query;
    string command;
    ofstream outstream;
};

#endif