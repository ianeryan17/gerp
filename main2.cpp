/*
 * Ryo Shimada and Ian Ryan
 * 11/30/22
 * 
 * This file acts as the main for stringProcessing.cpp.
 */

#include "stringProcessing.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iomanip>


using namespace std;

int main(int argc, char *argv[]){
    assert(stripNonAlphaNum("comp$15$63892###") == "comp$15$63892");
    assert(stripNonAlphaNum("c###c") == "c###c");
    assert(stripNonAlphaNum("comp") == "comp");
    assert(stripNonAlphaNum("c###") == "c");

    return 0;
}