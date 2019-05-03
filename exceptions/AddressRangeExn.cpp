#include "AddressRangeExn.hpp"

AddressRangeExn::AddressRangeExn(std::string msg) : std::runtime_error(msg) {
}
