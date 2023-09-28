//
// Created by harry on 9/21/23.
//

#ifndef INC_3520_PA01_PIPELINE_H
#define INC_3520_PA01_PIPELINE_H

#include <fstream>
#include <string>
#include <vector>
using std::string, std::ifstream, std::vector;

/**
 * Write the contents of reader into writer, excluding any HTML tags,
 * EXCEPT any preformatted text
 *
 * @param reader a file stream reading from the input file
 *
 * @return a vector of chars that is free of HTML tags (except preformatted)
 */
string deHTML(ifstream &reader);

/**
 * Converts an HTML entity into a character
 * An entity is a subset of escape characters (too many of those)
 *
 * @param entName The sequence to be interpreted
 * @return the translated character
 *         '?' if the sequence is not defined
 */
char interpretEntity(string entName);

/**
 * Breaks text into individual tokens
 * A token is a space-delimited sequence of characters
 *
 * @param sansHTML A constant reference to the string resulting from deHTML(), to be tokenized
 * @param tokens A reference to the vector to which all tokens will be added
 */
void tokenize(const string &sansHTML, vector<string> &tokens);

/**
 * Remove punctuation and special characters from tokens EXCEPT:
 * - any special characters or punctuation inside the HTML of a <pre>..</pre> tag
 *   ~ NOTE: pre tags are kept until this point, to make this distinction
 * - decimals in numbers
 * - apostrophes between two printable characters (e.g. it's)
 * - hyphens between two printable characters (e.g. super-duper), as opposed to hyphens surrounded partially or
 *   fully by whitespace
 * @param tokens A reference to the vector of tokens
 * @return
 */
void removePunc(vector<string> &tokens);

/**
 * Remove stop words from a given vector of tokens
 * A stop word is defined as any word in include/source/stopwords.txt
 *
 * @param tokens A reference to the vector of tokens
 * @return How many stop words were removed
 */
const unsigned int removeStops(vector<string> &tokens);

#endif //INC_3520_PA01_PIPELINE_H
