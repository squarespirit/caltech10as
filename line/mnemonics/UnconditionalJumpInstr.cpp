#include "UnconditionalJumpInstr.hpp"
#include "exceptions/RangeExn.hpp"

UnconditionalJumpInstr::UnconditionalJumpInstr(std::string const &opcode,
                                               Name const &label)
    : Mnemonic(opcode), label(label) {}

/**
 * Map of opcode -> high 3 bits of instruction.
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    {"CALL", 0b111}, {"JMP", 0b110},
};

bool UnconditionalJumpInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

uint16_t UnconditionalJumpInstr::encode(Context const &c) {
    number_t address = c.lookupLabel(label).getNumber();
    if (address >= PROGRAM_ADDRESS_SIZE) {
        throw RangeExn("Label address " + toHexString(address) +
                       " out of range");
    }
    return (codeMap.at(getOpcode()) << 13) + address;
}

bool UnconditionalJumpInstr::
operator==(const UnconditionalJumpInstr &other) const {
    return Mnemonic::operator==(other) && label == other.label;
}
