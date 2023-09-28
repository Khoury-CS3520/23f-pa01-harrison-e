#include "../../include/headers/pipeline.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using std::cout, std::cerr, std::endl,
std::ispunct, std::isalnum, std::isdigit,
std::ifstream;

// constants
const char TAG_OPEN    {'<'};
const char TAG_CLOSE   {'>'};
const char ENT_OPEN    {'&'};
const char ENT_CLOSE   {';'};
const char SPACE       {' '};
const char NEWLINE     {10};
const char HYPHEN      {'-'};
const char APOSTROPHE  {'\''};
const char PERIOD      {'.'};
const string OPEN_PRE  {"<pre>"};
const string CLOSE_PRE {"</pre>"};

string deHTML(ifstream &reader) {
    char currentChar {};        // character being read from input
    bool inPre {false};     // are we in a preformatted block?
    string output {};       // output string

    while (reader.get(currentChar)) {
        // read a tag
        if (currentChar == TAG_OPEN) {                  // current = <
            string tag {};
            if (inPre) {
                // check for ending of pre
                while (reader.get(currentChar) && currentChar != TAG_CLOSE)
                    tag += currentChar;
                if (tag.substr(0,4) == "/pre") {
                    inPre = false;
                    output += CLOSE_PRE; // keep for tokenization phase
                }
            } else {
                // check for beginning of pre
                while (reader.get(currentChar) && currentChar != TAG_CLOSE)
                    tag += currentChar;
                if (tag.substr(0,3) == "pre") {
                    inPre = true;
                    output += OPEN_PRE;  // keep for tokenization phase
                }
            }
        }

        // interpret an entity
        else if (currentChar == ENT_OPEN) {             // current = '&'
            string entName {};
            while (reader.get(currentChar) && currentChar != ENT_CLOSE) {
                entName += currentChar;
            }
            output += interpretEntity(entName);
        }

        else if (currentChar == NEWLINE && !inPre) {    // current = newline
            output += SPACE;
        }

        else {                                      // current != <, &, \n
            output += currentChar;
        }
    }
    // return string of input, sans html
    return output;
}

char interpretEntity(const string entName) {
    // ifs because switch doesn't work on string :(
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

void tokenize(const string &sansHTML, vector<string> &tokens) {
    string currentToken {};     // our current token (can have newlines)

    for (char currentChar : sansHTML) {
        if (currentChar == SPACE || currentChar == NEWLINE) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        } else {
            currentToken += currentChar;
        }
    }
    // loop over, push remaining token
    if (!currentToken.empty())
        tokens.push_back(currentToken);
}

void removePunc(vector<string> &tokens) {
    bool inPre {false};

    for (int i = 0; i < tokens.size(); i++) {
        if (inPre) {
            if (tokens.at(i) == CLOSE_PRE)
                inPre = false;
        } else if (tokens.at(i) == OPEN_PRE) {
            inPre = true;
        } else {
            // check first char
            if (ispunct(tokens.at(i).front()))
                tokens.at(i).erase(0,1);
            // check middle chars
            for (int j = 1; j < tokens.at(i).size() - 1; j++) {
                // if we find a decimal that is not surrounded by digits
                if (tokens.at(i).at(j) == PERIOD) {
                    if (!isdigit(tokens.at(i).at(j-1)) ||
                        !isdigit(tokens.at(i).at(j+1)))
                        tokens.at(i).erase(j,1);
                }
                // if we find an apostrophe or hyphen not between two printable chars
                else if (tokens.at(i).at(j) == APOSTROPHE ||
                         tokens.at(i).at(j) == HYPHEN) {
                    if (!isalnum(tokens.at(i).at(j-1)) ||
                        !isalnum(tokens.at(i).at(j+1)))
                        tokens.at(i).erase(j,1);
                }
                // if we find any other funky marks
                else {
                    if (ispunct(tokens.at(i).at(j)))
                        tokens.at(i).erase(j,1);
                }
            }
            // check last char
            if (ispunct(tokens.at(i).back()))
                tokens.at(i).erase(tokens.at(i).length()-1,1);
        }
    }
}

const unsigned int removeStops(vector<string> &tokens) {
    unsigned int numStopsRemoved {0};

    

    return numStopsRemoved;
}

