#include "ParseExn.hpp"

ParseExn::ParseExn(std::string msg) : std::runtime_error(msg) {
}

