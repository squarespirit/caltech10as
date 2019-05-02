#include "Register.hpp"

Register::Register(bool isX) {
    this->isX = isX;
}

bool Register::getIsX() {
    return isX;
}