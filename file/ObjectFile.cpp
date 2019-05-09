#include "ObjectFile.hpp"

ObjectFile::ObjectFile(std::string const &filename) : out(filename) {}

void ObjectFile::writeCode(uint16_t code) {
    out.write(reinterpret_cast<char *>(&code), sizeof(code));
}
