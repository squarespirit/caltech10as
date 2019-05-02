#include "AddressRangeExn.hpp"

AddressRangeExn::AddressRangeExn(std::string msg) {
    this->msg = msg;
}

const char* AddressRangeExn::what() const noexcept {
    return msg.c_str();
}