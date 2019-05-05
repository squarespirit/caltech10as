#include "ConditionalJumpInstr.hpp"
#include "exceptions/RangeExn.hpp"

ConditionalJumpInstr::ConditionalJumpInstr(std::string const &opcode,
                                           Name const &label)
    : Mnemonic(opcode), label(label) {}

/**
 * Map of opcode -> high 8 bits of instruction.
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    {"JA", 0x88},  {"JAE", 0x8C}, {"JNC", 0x8C}, {"JB", 0x8F},  {"JC", 0x8F},
    {"JBE", 0x8B}, {"JE", 0x9F},  {"JZ", 0x9F},  {"JG", 0xAF},  {"JGE", 0xBB},
    {"JL", 0xB8},  {"JLE", 0xAC}, {"JNE", 0x9C}, {"JNZ", 0x9C}, {"JNS", 0x98},
    {"JNU", 0xBC}, {"JNV", 0xA8}, {"JS", 0x9B},  {"JU", 0xBF},  {"JV", 0xAB}};

bool ConditionalJumpInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

uint16_t ConditionalJumpInstr::encode(Context const &c) {
    // Derivation:
    // new = old + r + 1
    // r = new - old - 1
    int relAddress =
        c.lookupLabel(label).getNumber() - c.getCurProgramAddress() - 1;
    if (relAddress < -128 || relAddress > 127) {
        throw RangeExn("Relative address " + std::to_string(relAddress) +
                       " is too far");
    }
    return (codeMap.at(getOpcode()) << 8) + uint8_t(relAddress);
}

bool ConditionalJumpInstr::operator==(const ConditionalJumpInstr &other) const {
    return Mnemonic::operator==(other) && label == other.label;
}
