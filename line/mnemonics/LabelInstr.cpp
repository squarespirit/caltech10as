#include "LabelInstr.hpp"
#include "ConditionalJumpInstr.hpp"
#include "UnconditionalJumpInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include <stdexcept>

std::unique_ptr<Mnemonic>
parseLabelInstr(std::string const &opcode,
                std::vector<std::string> const &operands) {
    if (!isValidLabelOpcode(opcode)) {
        throw ParseExn("Invalid opcode " + opcode + " for label instruction");
    }
    if (operands.size() != 1) {
        throw ParseExn(opcode + " requires 1 operand (got " +
                       std::to_string(operands.size()) + ")");
    }
    Name name = Name(operands[0]);
    if (ConditionalJumpInstr::isValidOpcode(opcode)) {
        return std::make_unique<ConditionalJumpInstr>(opcode, name);
    } else if (UnconditionalJumpInstr::isValidOpcode(opcode)) {
        return std::make_unique<UnconditionalJumpInstr>(opcode, name);
    }
    throw std::logic_error("No case for opcode");
}

bool isValidLabelOpcode(std::string const &opcode) {
    return ConditionalJumpInstr::isValidOpcode(opcode) ||
           UnconditionalJumpInstr::isValidOpcode(opcode);
}