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

    // Gerp Functions
    void determineQuery(string &query);

    // for testing
    vector<string> getContent();
    void makeIndex(DirNode* rootNode, string &dirName);
    void makeGerpFile(string &path);
    void open_or_die(ifstream &stream, string &fileName);

    struct gerpFile{
        string filePath;
        int startIndex;
    };

    GerpHash gerpHash;
    vector<string> content; // contains all the lines of every file
    int tracker;

private:
    vector<gerpFile> files;
};

#endif