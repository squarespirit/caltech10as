#include "ListingFile.hpp"
#include <iomanip>

ListingFile::ListingFile(std::string const &filename) : out(filename) {}

void ListingFile::writeLine(std::string const &source) {
    // Leave spacing as if prog address & code were there
    out << std::string(16, ' ') << source << std::endl;
}

void ListingFile::writeLine(number_t programAddress, uint16_t code,
                            std::string const &source) {
    // Write program address
    out << std::setfill('0') << std::setw(4) << std::hex << programAddress;
    // Write code
    out << std::string(4, ' ') << code;
    // Write source
    out << std::string(4, ' ') << source << std::endl;
}
