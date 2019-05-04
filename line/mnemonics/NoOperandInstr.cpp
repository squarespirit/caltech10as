#include "NoOperandInstr.hpp"

#include <unordered_map>
#include "exceptions/ParseExn.hpp"

/**
 * Map of opcode -> machine code of whole instruction.
 */
const std::unordered_map<std::string, uint16_t> codeMap = {
    // ALU instructions
    {"ASR", 0x7101},
    {"DEC", 0x7D00},
    {"INC", 0x0000},
    {"LSL", 0x5800},
    {"LSR", 0x7100},
    {"NEG", 0x2700},
    {"NOT", 0x2D00},
    {"RLC", 0x5000},
    {"ROL", 0x5200},
    {"ROR", 0x7102},
    {"RRC", 0x7103},

    // Flag instructions
    {"STI", 0x7F81},
    {"CLI", 0x0769},
    {"STU", 0x7F22},
    {"CLU", 0x07CA},
    {"STC", 0x7F0C},
    {"CLC", 0x07E4},

    // Index register instructions
    {"TAX", 0x0780},
    {"TXA", 0x6701},
    {"INX", 0x0580},
    {"DEX", 0x0D80},
    {"TAS", 0x0750},
    {"TSA", 0x6700},
    {"INS", 0x0640},
    {"DES", 0x0E40},

    // Control flow instructions
    {"RTS",   0x1F00},
    {"POPF",  0x0200},
    {"PUSHF", 0x0E00},

    // Misc instructions
    {"NOP", 0x1F80}
};

NoOperandInstr::NoOperandInstr(std::string const &opcode) : Mnemonic(opcode) {}

bool NoOperandInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

std::unique_ptr<NoOperandInstr> NoOperandInstr::parseOp(
        std::string const &opcode, std::vector<std::string> const &operands) {
    if (!isValidOpcode(opcode)) {
        throw ParseExn("Unknown opcode " + opcode + " for no-operand instruction");
    }
    if (operands.size() != 0) {
        throw ParseExn(opcode + " must take 0 operands (got " + std::to_string(operands.size()) + ")");
    }
    return std::make_unique<NoOperandInstr>(opcode);
}

uint16_t NoOperandInstr::encode(Context const &c) {
    return codeMap.at(getOpcode());
}
