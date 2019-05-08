#pragma once
#include <string>
#include <vector>

/**
 * A C-string containing the horizontal whitespace characters.
 */
extern const char *WHITESPACE;

/**
 * Return whether the character is whitespace (space or tab).
 * Only horizontal whitespace is considered. (\n is *not* considered
 * whitespace.)
 */
bool isWhitespace(char c);

/**
 * Trim whitespace from the beginning and end of a string in-place.
 */
void trimWhitespace(std::string &s);

/**
 * Split a string around whitespace.
 * Return a vector of tokens. These are the text between the whitespace,
 * in the order they appear in the original string.
 *
 * Consecutive runs of whitespace are considered to be a single delimiter
 * between tokens.
 * If the string begins with whitespace, the first element will be "".
 * Likewise, if the string ends with whitespace, the last element will be "".
 */
std::vector<std::string> splitWhitespace(std::string const &s);