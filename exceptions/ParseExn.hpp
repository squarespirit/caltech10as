#pragma once
#include "AssemblyExn.hpp"
#include <string>

/**
 * ParseExn is an exception thrown when failing to convert a string to an
 * object.
 */
class ParseExn : public AssemblyExn {
public:
    explicit ParseExn(std::string const &msg);
};