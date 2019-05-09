#pragma once
#include "AssemblyExn.hpp"
#include <string>

/**
 * RangeExn is an exception thrown when a number (address or data value) is
 * out of range.
 */
class RangeExn : public AssemblyExn {
public:
    explicit RangeExn(std::string const &msg);
};