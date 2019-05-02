#include "Name.hpp"
#include "exceptions/ParseExn.hpp"
#include <cctype>

Name::Name(std::string name) {
    if (name.length() == 0) {
        throw ParseExn("Cannot have empty name");
    }
    
    if (!isalpha(name[0]) && name[0] != '_') {
        throw ParseExn("Invalid name " + name + ": first letter must be alphabetic or underscore");
    }

    for (int i = 1; i < name.length(); i++) {
        if (!isalnum(name[i]) && name[i] != '_') {
            throw ParseExn("Invalid name " + name + ": letters after the first must be alphanumeric or underscore");
        }
    }

    this->name = name;
}

std::string Name::getName() {
    return name;
}