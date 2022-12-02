/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for FSTree.h. This is the one I'm working on.
 */

#include "stringProcessing.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>


using namespace std;

string stripNonAlphaNum(string input){
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
        cerr << "output: " << output << endl;

    }
    return output;
}

bool isAlphaChar(char c){
    if((int(c) <= 57 and int(c) >= 48) or (int(c) <= 90 and int(c) >= 65)){
        return true;
    } else if(int(c) <= 122 and int(c) >= 97){
        return true;
    } else {
        return false;
    }
}