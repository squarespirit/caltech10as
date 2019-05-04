#include "ParseExn.hpp"

ParseExn::ParseExn(std::string const &msg) : std::runtime_error(msg) {
}

