#include "Register.hpp"
#include "exceptions/ParseExn.hpp"

Register::Register(bool isX) { this->isX = isX; }

bool Register::getIsX() const { return isX; }

Register Register::parse(std::string const &s) {
    if (s == "S") {
        return Register(false);
    } else if (s == "X") {
        return Register(true);
    }
    throw ParseExn("Invalid register " + s);
}

const Register Register::S = Register(false);

const Register Register::X = Register(true);

bool Register::operator==(Register const &other) const {
    return isX == other.isX;
}
