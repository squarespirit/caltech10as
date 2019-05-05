#include "DirectInstr.hpp"
#include "exceptions/RangeExn.hpp"

DirectInstr::DirectInstr(std::string const &opcode, Symbol const &dataAddress)
    : Mnemonic(opcode), dataAddress(dataAddress) {}

/**
 * Map of opcode -> top 8 bits of instruction.
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    // Load/store
    {"LDD", 0x80},
    {"STD", 0xA0},

    // I/O
    {"IN", 0x90},
    {"OUT", 0xB0}};

bool DirectInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

uint16_t DirectInstr::encode(Context const &c) {
    number_t address = dataAddress.resolve(c);
    if (address >= DATA_ADDRESS_SIZE) {
        throw RangeExn("Data address " + toHexString(address) +
                       " out of range");
    }
    return (codeMap.at(getOpcode()) << 8) + address;
}

bool DirectInstr::operator==(DirectInstr const &other) const {
    return Mnemonic::operator==(other) && dataAddress == other.dataAddress;
}