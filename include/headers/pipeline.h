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
 * EXCEPT any preformatted tags
 *
 * @param reader a file stream reading from the input file
 * @return a vector of chars that is free of HTML tags (except preformatted)
 */
string removeHTML(ifstream &reader);

/**
 * Convert an HTML entity into a character
 * An entity is a subset of escape characters (too many of those)
 *
 * @param entName The sequence to be interpreted
 * @return the translated character
 *         '?' if the sequence is not defined
 */
char interpretEntity(string entName);

/**
 * Break text into individual tokens
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
 *
 * @param tokens A reference to the vector of tokens
 */
void removePunc(vector<string> &tokens);

/**
 * Determine if the input string is a stop word
 * A stop word is defined as any word in the vector stopWords
 *
 * @param s The string to be tested
 * @return True if it is a stop word, False otherwise
 */
bool isStopWord(string &s);

/**
 * Remove stop words from a given vector of tokens
 *
 * @param tokens A reference to the vector of tokens
 * @return How many stop words were removed
 */
const unsigned int removeStops(vector<string> &tokens);

/**
 * Do some final polishing on tokens, removing empty tokens and pre tags
 *
 * @param tokens A reference to the vector of tokens
 * @return The total number of chars in the vector, after polishing
 */
const unsigned int polishTokens(vector<string> &tokens);

#endif //INC_3520_PA01_PIPELINE_H
