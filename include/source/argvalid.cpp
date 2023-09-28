#include "../../include/headers/argvalid.h"
#include <iostream>
#include <fstream>
using std::cout, std::cerr, std::endl, std::ifstream, std::ofstream;


bool validArgs(int argc, char* argv[]) {
    const int CORRECT_ARGS {3};

    switch (argc) {
        case 1:
        case 2:
            cerr << "Error: Too few arguments" << endl;
            return false;
        case CORRECT_ARGS:
            break;
        default:
            cerr << "Error: Too many arguments" << endl;
            return false;
    }

    // instantiate test streams (and close them later)
    ifstream testIn (argv[1]);
    ofstream testOut (argv[2]);

    if (!testIn) {  // input file cannot be opened
        cerr << "Error: Input file cannot be opened" << endl;
        testIn.close();
        testOut.close();
        return false;
    }
    if (!testOut) { // output file cannot be opened
        cerr << "Error: Output file cannot be opened" << endl;
        testIn.close();
        testOut.close();
        return false;
    }

    // all tests passed, args are valid
    testIn.close();
    testOut.close();
    return true;
}