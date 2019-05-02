#pragma once
#include <string>

class Name {
public:
    /**
     * Convert a string to a name. Throw a ParseExn if it cannot be converted.
     * The first character must be alphabetic or underscore. Subsequent
     * characters must be alphanumeric or underscore.
     */
    Name(std::string name);
    std::string getName();
private:
    std::string name;
};