#pragma once
#include <stdexcept>
#include <string>

/**
 * RangeExn is an exception thrown when a number (address or data value) is
 * out of range.
 */
class RangeExn : public std::runtime_error {
public:
    explicit RangeExn(std::string const &msg);
};