/*
 * Ryo Shimada and Ian Ryan
 * 12/7/22
 * 
 * This file acts as the main for gerp.cpp.
 */

#include "gerp.h"
#include "gerpHash.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        cerr << "Usage: ./gerp inputDirectory outputFile";
        return 1;
    }
    string inputDir = argv[1];
    string outputFile = argv[2];
    FSTree tree(inputDir);
    DirNode* root = tree.getRoot();
    Gerp gerp_engine;
    gerp_engine.runGerp(root, inputDir, outputFile);
    return 0;
}