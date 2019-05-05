#include "RangeExn.hpp"

RangeExn::RangeExn(std::string const &msg) : std::runtime_error(msg) {}
