#include "UnconditionalJumpInstr.hpp"
#include "exceptions/RangeExn.hpp"

UnconditionalJumpInstr::UnconditionalJumpInstr(std::string const &opcode,
                                               Name const &name)
    : Mnemonic(opcode), name(name) {}

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
    number_t address = c.lookupLabel(name).getNumber();
    if (address >= PROGRAM_ADDRESS_SIZE) {
        throw RangeExn("Label address " + toHexString(address) +
                       " out of range");
    }
    return (codeMap.at(getOpcode()) << 13) + address;
}
