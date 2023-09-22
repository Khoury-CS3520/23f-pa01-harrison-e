#include "../../include/headers/pipeline.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout, std::cerr, std::endl,
      std::ifstream, std::string;

string deHTML(ifstream &reader) {
    // constants
    const char TAG_OPEN  {'<'};
    const char TAG_CLOSE {'>'};
    const char ENT_OPEN  {'&'};
    const char ENT_CLOSE {';'};

    // variables
    char current {};        // character being read from input
    bool inPre {false};     // are we in a preformatted block?

    string output;    // output string

    while (reader.get(current)) {
        // read a tag
        if (current == TAG_OPEN) {      // current = <
            string tag {};
            if (inPre) {
                // check for ending of pre
                while (reader.get(current) && current != TAG_CLOSE)
                    tag += current;
                if (tag.substr(0,4) == "/pre")
                    inPre = false;
            } else {
                // check for beginning of pre
                while (reader.get(current) && current != TAG_CLOSE)
                    tag += current;
                if (tag.substr(0,3) == "pre")
                    inPre = true;
            }
        }

        // interpret an entity
        else if (current == ENT_OPEN) {     // current = '&'
            string entName {};
            while (reader.get(current) && current != ENT_CLOSE) {
                entName += current;
            }
            output += interpretEntity(entName);
        }

        else if (current == 10) {           // current = newline
            output += ' ';
        }

        else {
            // current != <, >, &
            output += current;
        }
    }
    // return string of input, sans html
    return output;
}

char interpretEntity(string entName) {
    // ifs because switch doesnt work on string :(
    if      (entName == "NewLine")
        return '\n';
    else if (entName == "nbsp")
        return ' ';
    else if (entName == "quot")
        return '"';
    else if (entName == "amp")
        return '&';
    else if (entName == "lt")
        return '<';
    else if (entName == "gt")
        return '>';
    else
        return '?';
}