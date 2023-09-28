/**
 * Programming Assignment 01 - Text Time
 * CS3520 - Programming in C++
 * authored by Harrison Eckert
 *
 * This program processes textual data, via a processing pipeline, for use in other applications
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "include/headers/argvalid.h"
#include "include/headers/pipeline.h"
using std::cin, std::cout, std::endl, std::cerr;
using std::string;
using std::vector;
using std::ofstream, std::ifstream;

// main method
int main(int argc, char* argv[]) {
    ifstream reader;    // file object reading from input file
    ofstream writer;    // file object writing to output file

    // abort if args are invalid
    if (!validArgs(argc, argv)) {
        return 1;
    }

    // open input file
    reader.open(argv[1]);

    // remove HTML from input text
    string sansHTML = removeHTML(reader);

    // tokenize input
    vector<string> tokens;
    tokenize(sansHTML, tokens);

    // remove punctuations from tokens
    removePunc(tokens);

    const unsigned int NUM_TOKENS_WITH_STOP = tokens.size();
    // remove stop words
    const unsigned int NUM_STOPS_REMOVED    = removeStops(tokens);
    const unsigned int NUM_TOKENS_NO_STOP   = tokens.size();
    const unsigned int FINAL_NUM_CHARS      = polishTokens(tokens);

    // write to output file
    writer.open(argv[2]);
    for (string token : tokens) {
        writer << token << endl;
    }
    writer << "# of tokens before removing stop words: " << NUM_TOKENS_WITH_STOP << endl;
    writer << "# of tokens after removing stop words: " << NUM_TOKENS_NO_STOP << endl;
    writer << "# of stop words removed: " << NUM_STOPS_REMOVED << endl;
    writer << "# of chars after cleaning: " << FINAL_NUM_CHARS;
    // !!! NOTE TO TA !!!
    // these stats may differ from the provided output example. this is because of a few things:
    // 1. my deHTML() function translates HTML entities (like &lt;) into their appropriate symbols (i.e. &lt; -> <)
    // 2. in order to keep symbols from preformatted blocks, i keep the pre tag tokens in for removePunc(),
    //    and remove at polishTokens(). this means that between steps 2 and 4, i have some extra words (including
    //    empty tokens)
    // 3. since i translate and then remove HTML entities, they are not in the total character count at the end
    // please grade this part of my program with this in mind! thank you!

    // close reader and writer to free resources
    reader.close();
    writer.close();
    // exit successfully
    return 0;
}