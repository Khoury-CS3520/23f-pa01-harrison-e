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
 * 1. remove useless information
 *  - remove all HTML tags (ex. <li>, </li>, <!DOCTYPE html>)
 *  - NOTE: anything that is within \<pre\>..\</pre\> tags should be retained!
 *
 * 2. tokenize
 *  - break the remaining text into an order sequence of individual tokens
 *  - a _token_ is a space delimited sequence of characters
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

    reader.open(argv[1]);

    // remove HTML from input text
    string sansHTML = deHTML(reader);

    // test functionality

    /**
    // test deHTML()
    cout << "input without html:" << endl;
    for (char& c : sansHTML) {
        cout << c;
    }
    */

    // TODO: tokenize
    vector<string> tokens;
    // tokenize w/ references
    tokenize(sansHTML, tokens);
    // testing tokenize()
    cout << "Tokenized input: " << endl;
    for (string token : tokens) {
        cout << token << endl;
    }

    // TODO: remove stop words
    // removeStops();

    // TODO: clean up text
    // clean();

    // write to output file

    // the rest...
    cout << "rest of the program..." << endl;

    // close reader and writer to free resources
    reader.close();
    writer.close();
    // exit successfully
    return 0;
}




