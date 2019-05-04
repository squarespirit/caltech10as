#include "Number.hpp"
#include "exceptions/ParseExn.hpp"

/**
 * Convert hex character to integer value.
 * Return -1 for unknown character.
 */
int hexToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <='f') {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <='F') {
        return c - 'A' + 10;
    }
    return -1;
}


Number::Number(std::string s) {
    if (s.length() == 0) {
        throw ParseExn("Cannot parse number from empty string");
    }
    if (s.length() > NUMBER_MAX_DIGITS) {
        throw ParseExn("Number " + s + " too large, at most " + std::to_string(NUMBER_MAX_DIGITS) + " digits");
    }

    number = 0;
    for (size_t i = 0; i < s.length(); i++) {
        number <<= 4;
        int digit = hexToInt(s[i]);
        if (digit == -1) {
            throw ParseExn("Invalid digit " + std::to_string(s[i]) + " in number " + s);
        }
        number += digit;
    }
}

Number::Number(number_t n) {
    number = n;
}

number_t Number::getNumber() const {
    return number;
}

bool Number::operator==(const Number &other) const {
    return this->number == other.number;
}

