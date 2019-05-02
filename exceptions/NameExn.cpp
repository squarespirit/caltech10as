#include "NameExn.hpp"

NameExn::NameExn(std::string msg) {
    this->msg = msg;
}

const char* NameExn::what() const noexcept {
    return msg.c_str();
}
