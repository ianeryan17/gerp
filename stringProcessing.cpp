/*
 * Ryo Shimada and Ian Ryan
 *
 * 11/30/22
 * 
 * This file acts as the implementation for stringProcessing.h.
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

// Input: string input
// Output: string output
// Purpose: this function removes all leading and trailing non-alphanumeric
// characters from the given input string.
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
    }
    return output;
}

// Input: char c
// Output: boolean
// Purpose: this function takes a given input character and determines whether
// the character is an alphanumeric character or not, returning true if the
// chracter is an alphanumeric char.
bool isAlphaChar(char c){
    if((int(c) <= 57 and int(c) >= 48) or (int(c) <= 90 and int(c) >= 65)){
        return true;
    } else if(int(c) <= 122 and int(c) >= 97){
        return true;
    } else {
        return false;
    }
}