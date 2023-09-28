#include "../../include/headers/pipeline.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
using std::cout, std::cerr, std::endl,
std::ispunct, std::isalnum, std::isdigit,
std::ifstream, std::find, std::remove_if,
std::tolower;

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
            if (!tokens.at(i).empty()) {
                for (int j = 1; j < tokens.at(i).length() - 1; j++) {
                    // if we find a decimal that is not surrounded by digits
                    if (tokens.at(i).at(j) == PERIOD) {
                        if (tokens.at(i).length() >= 3 &&
                            !isdigit(tokens.at(i).at(j - 1)) ||
                            !isdigit(tokens.at(i).at(j + 1)))
                            tokens.at(i).erase(j, 1);
                    }
                        // if we find an apostrophe or hyphen not between two printable chars
                    else if (tokens.at(i).at(j) == APOSTROPHE ||
                              tokens.at(i).at(j) == HYPHEN) {
                        if (tokens.at(i).length() >= 3 &&
                            !isalnum(tokens.at(i).at(j - 1)) ||
                            !isalnum(tokens.at(i).at(j + 1)))
                            tokens.at(i).erase(j, 1);
                    }
                        // if we find any other funky marks
                    else {
                        if (!tokens.at(i).empty() &&
                            ispunct(tokens.at(i).at(j)))
                            tokens.at(i).erase(j, 1);
                    }
                }
            }
            // check last char
            if (!tokens.at(i).empty() &&
                ispunct(tokens.at(i).back())) {
                tokens.at(i).erase(tokens.at(i).length() - 1, 1);
            }
        }
    }
}

bool isStopWord(string &s) {
    vector<string> stopWords = {
            "i", "me", "my", "myself", "we", "our", "ours", "ourselves",
            "you", "your", "yours", "yourself", "yourselves", "he", "him",
            "his", "himself", "she", "her", "hers", "herself", "it", "its",
            "itself", "they", "them", "their", "theirs", "themselves", "what",
            "which", "who", "whom", "this", "that", "these", "those", "am", "is",
            "are", "was", "were", "be", "been", "being", "have", "has", "had",
            "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but",
            "if", "or", "because", "as", "until", "while", "of", "at", "by", "for",
            "with", "about", "against", "between", "into", "through", "during",
            "before", "after", "above", "below", "to", "from", "up", "down", "in",
            "out", "on", "off", "over", "under", "again", "further", "then", "once",
            "here", "there", "when", "where", "why", "how", "all", "any", "both",
            "each", "few", "more", "most", "other", "some", "such", "no", "nor",
            "not", "only", "own", "same", "so", "than", "too", "very", "s", "t",
            "can", "will", "just", "don", "should", "now"
    };

    string ls = {};
    for (char c : s) {
        ls += tolower(c);
    }

    // search for lowercase s in stopWords
    if(find(stopWords.begin(), stopWords.end(), ls) != stopWords.end())
        return true;

    return false;
}

const unsigned int removeStops(vector<string> &tokens) {
    const unsigned int ORIG_SIZE = tokens.size();
    tokens.erase(remove_if(tokens.begin(), tokens.end(),
                           [](string t){ return isStopWord(t); }), tokens.end());
    return ORIG_SIZE - tokens.size();
}

const unsigned int polishTokens(vector<string> &tokens) {
    tokens.erase(remove_if(tokens.begin(), tokens.end(),
                           [](string t) { return (t == "" || t == OPEN_PRE || t == CLOSE_PRE);}),
                 tokens.end());
    unsigned int charsCount {0};
    for (string token : tokens) {
        for (char c : token) {
            charsCount++;
        }
    }
    return charsCount;
}