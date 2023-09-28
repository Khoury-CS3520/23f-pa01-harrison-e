//
// Created by harry on 9/21/23.
//

#ifndef INC_3520_PA01_ARGVALID_H
#define INC_3520_PA01_ARGVALID_H

/**
 * Validates that arguments passed to main() can be used by the pipeline
 *
 * @param argc The number of arguments passed to main
 * @param argv The arguments passed to main as an array of char[]s
 * @return true if the arguments are valid (argc == 3, input and output files are usable),
 *         false otherwise
 */
bool validArgs(int argc, char* argv[]);

#endif //INC_3520_PA01_ARGVALID_H
