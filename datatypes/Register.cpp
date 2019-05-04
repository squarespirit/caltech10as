#include "Register.hpp"
#include "exceptions/ParseExn.hpp"

Register::Register(bool isX) {
    this->isX = isX;
}

bool Register::getIsX() const {
    return isX;
}

Register Register::parse(std::string s) {
    if (s == "S") {
        return Register(false);
    } else if (s == "X") {
        return Register(true);
    }
    throw ParseExn("Invalid register " + s);
}

bool Register::operator==(Register const &other) const {
    return isX == other.isX;
}
