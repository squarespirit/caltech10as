#include "Mnemonic.hpp"

Mnemonic::Mnemonic(std::string const &opcode) : opcode(opcode) {}

bool Mnemonic::operator==(const Mnemonic &other) const {
    return opcode == other.opcode;
}

std::string Mnemonic::getOpcode() { return opcode; }
