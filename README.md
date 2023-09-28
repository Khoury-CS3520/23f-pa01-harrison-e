# PA01 - Text Time

This is the first programming assignment for CS 3520 - Fall 2023 - Section 01 with Dr. Fontenot. 

All code authored by Harrison Eckert.

## Overview
This program processes textual data, via a processing pipeline, for use in other applications.

## Usage
To use this program, build with CMake, and then type into a terminal:

`./[executable_name] [input_file.html] [output_file.txt]`,

replacing `[executable_name]` with the name of your compiled version of the source,
`[input_file.html]` with the input file you want to parse (does not have to have .html extension),
and `[output_file.html]` with the output file you want to write to.

## Technical Details
This program is divided into a multitude of functions, most of which are described in `include/headers/pipeline.h`, and 
implemented in `include/source/pipeline.cpp`. 

This section provides a brief overview of each function apart from `main`. 
For additional details and clarifications, including data types and implementation, please see `/include/headers/` and
`/include/source/`, respectively.

### `validArgs()`
This function validates the arguments passed into the main function from the command line.
It returns `true` if the arguments are valid, and false otherwise.
Valid arguments are defined by a few traits:
- `argc` is 3, meaning that there is exactly 1 input file and 1 output file provided
- the input file can be successfully opened
- the output file can be successfully opened 

### `removeHTML()`
This function takes a reference to an input file stream reading from the input file, and produces a string of the 
file's contents, without any HTML tags EXCEPT `<pre>` and `</pre>` tags. 

Preformatted tags are retained so that preformatted punctuation is not deleted later in the processing pipeline.

### `interpretEntity()`
This function takes a string to be interpreted as an HTML entity, and returns its corresponding character.
If there is no corresponding character, it returns (`?`)

### `tokenize()`
This function takes a reference to a string (the string produced by `removeHTML()`),
and a reference to a vector of strings. 
Functionally, it tokenizes the input string, pushing each token onto the vector.

A token is defined as a whitespace-delimited sequence of characters.

This function does not return anything.

### `removePunc()`
This function takes a reference to the vector of strings (tokens), and removes any punctuation or special characters,
EXCEPT:
- any special characters or punctuation inside of `<pre>..</pre>`
  - pre tags are kept for this step, and removed in a final polishing of the tokens
- decimals in numbers
- apostrophes between two printable characters
  - ex.: it's, how's, doesn't
- hyphens between two printable characters
  - ex.: how-to, pre-K, super-duper

This function does not return anything.

### `isStopWord()`
This function takes a reference to a string, and determines if it is a stop word. 
This function is used as a helper for `removeStops()`.

If the input string is a stop word, the function returns `true`. Otherwise, it returns `false`.

A stop word is defined [by this gist.](https://gist.github.com/sebleier/554280)

### `removeStops()`
This function takes a reference to the vector of strings (tokens), and removes any token that is a stop word, 
using `isStopWord()`.

It returns the number of stop words it removed.

### `polishTokens()`
This function takes a reference to the vector of strings (tokens), and does some final polishing, by removing any
leftover `<pre>` and `</pre` tokens, and any empty tokens (`""`).

It returns the total number of characters between all tokens, after cleaning.