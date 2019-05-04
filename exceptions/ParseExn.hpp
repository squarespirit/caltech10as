#pragma once
#include <stdexcept>
#include <string>

/**
 * ParseExn is an exception thrown when failing to convert a string to an
 * object.
 */
class ParseExn : public std::runtime_error {
public:
    explicit ParseExn(std::string const &msg);
};