#include "NumberTypes.hpp"
#include <sstream>

std::string toHexString(number_t n) {
    std::stringstream stream;
    stream << std::hex << n;
    return stream.str();
}