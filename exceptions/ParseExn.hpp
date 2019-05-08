#pragma once
#include <string>
#include "AssemblyExn.hpp"

/**
 * ParseExn is an exception thrown when failing to convert a string to an
 * object.
 */
class ParseExn : public AssemblyExn {
public:
    explicit ParseExn(std::string const &msg);
};