#include "ImmediateInstr.hpp"
#include "exceptions/RangeExn.hpp"
#include <unordered_map>

ImmediateInstr::ImmediateInstr(std::string const &opcode, Symbol const &s)
    : Mnemonic(opcode), dataValue(s) {}

/**
 * Map of opcode -> high 8 bits of instruction. (The immediate value is encoded
 * in the low 8 bits.)
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    // ALU instructions
    {"ADCI", 0x63},
    {"ADDI", 0x6B},
    {"ANDI", 0x47},
    {"CMPI", 0x33},
    {"ORI", 0x77},
    {"SBBI", 0x1B},
    {"SUBI", 0x13},
    {"TSTI", 0x4F},
    {"XORI", 0x37},

    // LDI
    {"LDI", 0x89}};

bool ImmediateInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

uint16_t ImmediateInstr::encode(Context const &c) {
    number_t value = dataValue.resolve(c);
    if (value >= DATA_VALUE_SIZE) {
        throw RangeExn("Data value " + toHexString(value) + " out of range");
    }
    return (codeMap.at(getOpcode()) << 8) + value;
}

bool ImmediateInstr::operator==(ImmediateInstr const &other) const {
    return Mnemonic::operator==(other) && dataValue == other.dataValue;
}
