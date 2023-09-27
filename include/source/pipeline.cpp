#include "../../include/headers/pipeline.h"
#include <iostream>
#include <string>
using std::cout, std::cerr, std::endl;

// constants
const char TAG_OPEN  {'<'};
const char TAG_CLOSE {'>'};
const char ENT_OPEN  {'&'};
const char ENT_CLOSE {';'};
const char SPACE     {' '};
const char NEWLINE   {10};

string deHTML(ifstream &reader) {
    char current {};        // character being read from input
    bool inPre {false};     // are we in a preformatted block?
    string output {};          // output string

    while (reader.get(current)) {
        // read a tag
        if (current == TAG_OPEN) {                  // current = <
            string tag {};
            if (inPre) {
                // check for ending of pre
                while (reader.get(current) && current != TAG_CLOSE)
                    tag += current;
                if (tag.substr(0,4) == "/pre") {
                    inPre = false;
                    output += "</pre>"; // keep for tokenization phase
                }
            } else {
                // check for beginning of pre
                while (reader.get(current) && current != TAG_CLOSE)
                    tag += current;
                if (tag.substr(0,3) == "pre") {
                    inPre = true;
                    output += "<pre>";  // keep for tokenization phase
                }
            }
        }

        // interpret an entity
        else if (current == ENT_OPEN) {             // current = '&'
            string entName {};
            while (reader.get(current) && current != ENT_CLOSE) {
                entName += current;
            }
            output += interpretEntity(entName);
        }

        else if (current == NEWLINE && !inPre) {    // current = newline
            output += SPACE;
        }

        else {                                      // current != <, &, \n
            output += current;
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
    bool inPre {false};         // are we in a preformatted block?
    string currentToken {};     // our current token (can have newlines)
    string currentWord  {};     // our current word  (no newlines, only used for pre)

    for (char current : sansHTML) {
        currentToken += current;
        currentWord  += current;

        // handle preformatted token
        if (inPre) {
            // words do not include newlines or spaces
            if (current == NEWLINE || current == SPACE) {
                currentWord = "";
            }

            // could we be starting a closing pre?
            // if we see <, reset current word (accommodate for irregular <)
            else if (current == TAG_OPEN) {
                currentWord = TAG_OPEN;
            }

            // are we ending the pre block?
            else if (current == TAG_CLOSE && currentWord.substr(0,5) == "</pre>") {
                tokens.push_back(currentToken);
                currentToken = "";
                currentWord  = "";
                inPre = false;
            }

            // if none of these, retain the current word and token
        }

        // could we be starting a pre tag?
        // if we see <, reset current word (accommodate for irregular < placement)
        else if (current == TAG_OPEN) {
            currentWord = TAG_OPEN;
        }

        // could we be starting a pre?
        // if we see e, check current word
        else if (current == 'e' && currentWord == "<pre") {
            inPre = true;
        }

        // if we reach delimiter and NOT in pre
        else if (current == SPACE) {
            // to see if we really have a token, remove the space
            string tokenNoSpace {currentToken.substr(0, currentToken.length() - 1)};
            // if we have a token, push it to vec
            if (!tokenNoSpace.empty())
                tokens.push_back(currentToken);
            // either way, reset token and word
            currentToken = "";
            currentWord = "";
        }
    }
    // loop over, push remaining token
    if (!currentToken.empty())
        tokens.push_back(currentToken);
}

