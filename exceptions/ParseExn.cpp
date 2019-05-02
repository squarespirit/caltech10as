#include "ParseExn.hpp"

ParseExn::ParseExn(std::string msg) {
    this->msg = msg;
}

const char* ParseExn::what() const noexcept {
    return msg.c_str();
}


