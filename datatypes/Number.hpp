#pragma once
#include "NumberTypes.hpp"
#include <string>

#define NUMBER_MAX_DIGITS (sizeof(number_t) * 2)

class Number {
public:
    /**
     * Convert a string to a number. Throw an exception if it cannot be
     * converted. All numbers are non-negative hexadecimal.
     */
    explicit Number(std::string number_s);
    /**
     * Construct a number directly.
     */
    explicit Number(number_t number);

    number_t getNumber() const;

    bool operator==(const Number &) const;

private:
    number_t number;
};