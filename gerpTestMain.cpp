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
    gerp_engine.makeIndex(root, inputDir);
    gerp_engine.determineQuery();

    // Test for tinyData:
    // for(int i = 0; i < gerp_engine.gerpHash.senseHash.at(9785).size(); i++){
    //     cerr << "at(" << i << "): " << gerp_engine.gerpHash.senseHash.at(9785).at(i).wordString << endl;
    //     for(int j = 0; j < gerp_engine.gerpHash.senseHash.at(9785).at(i).lineLocation.size(); j++){
    //         cerr << "locations for we: " << gerp_engine.gerpHash.senseHash.at(9785).at(i).lineLocation.at(j) << endl;

    //     }
    // }

    // size = 10
    // cerr << "test main size: " << gerp_engine.gerpHash.senseHash->at(60).size() << endl;
    // for(int i = 0; i < gerp_engine.gerpHash.senseHash->at(60).size(); i++){
    //     cerr << "at(" << i << "): " << gerp_engine.gerpHash.senseHash->at(60).at(i).wordString << endl;
    //     for(int j = 0; j < gerp_engine.gerpHash.senseHash->at(60).at(i).lineLocation.size(); j++){
    //         cerr << "locations for we: " << gerp_engine.gerpHash.senseHash->at(60).at(i).lineLocation.at(j) << endl;

    //     }
    // }
    return 0;
}