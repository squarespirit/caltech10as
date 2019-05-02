#pragma once
#include <string>
#include <cstdint>

/** The type of numbers. */
typedef uint16_t number_t;
#define NUMBER_MAX_DIGITS (sizeof(number_t) * 2)

class Number {
public:
    /**
     * Convert a string to a number. Throw an exception if it cannot be
     * converted. All numbers are non-negative hexadecimal.
     */
    Number(std::string number_s);
    number_t getNumber();
private:
    number_t number;
};