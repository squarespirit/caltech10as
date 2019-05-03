#include "RangeExn.hpp"

RangeExn::RangeExn(std::string msg) : std::runtime_error(msg) {
}
