/**
 * Programming Assignment 01 - Text Time
 * CS3520 - Programming in C++
 * authored by Harrison Eckert
 *
 * This program processes textual data, via a processing pipeline, for use in other applications
 */

/**
 * INPUT:
 * - textual information in a file, that may include HTML
 * - the name of the input file is provided as a command line arg (argv[1])
 */

/**
 * PROCESSING PIPELINE:
 *
 * 3. remove stop words
 *  - remove stop words (words that do not contribute to the meaning of the text)
 *  - stop words listed at https://gist.github.com/sebleier/554280
 *
 * 4. clean up the text
 *  - remove all punctuation except:
 *    - any special characters or punctuation inside the HTML of a <pre>..</pre> tag
 *    - decimals in numbers
 *    - apostrophes between two printable characters (e.g. it's)
 *    - hyphens between two printable characters (e.g. super-duper), as opposed to hyphens surrounded partially or
 *      fully by whitespace
 */

/**
 * OUTPUT:
 * - refined textual information piped into output file
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
    string sansHTML = deHTML(reader);

    /**
    // test deHTML()
    cout << "input without html:" << endl;
    for (char& c : sansHTML) {
        cout << c;
    }
    */

    vector<string> tokens;
    tokenize(sansHTML, tokens);
    const unsigned long NUM_TOKENS_WITH_STOP = tokens.size();

    // testing tokenize()
    cout << "Tokenized input: " << endl;
    for (string token : tokens) {
        cout << token << endl;
    }
    cout << "# of tokens before removing stop words: " << NUM_TOKENS_WITH_STOP << endl;

    // remove punctuations from tokens
    removePunc(tokens);

    // TODO: remove stop words
    // const unsigned int NUM_STOPS_REMOVED = removeStops(tokens);
    // const unsigned long NUM_TOKENS_NO_STOP = tokens.size();

    // TODO: clean up text
    // cleanTokens();
    // const int NUM_CHARS


    // TODO: stats!

    // write to output file

    // close reader and writer to free resources
    reader.close();
    writer.close();
    // exit successfully
    return 0;
}




