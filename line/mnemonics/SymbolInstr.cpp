#include "SymbolInstr.hpp"
#include "DirectInstr.hpp"
#include "ImmediateInstr.hpp"
#include "exceptions/ParseExn.hpp"

bool isValidSymbolInstrOpcode(std::string const &opcode) {
    return DirectInstr::isValidOpcode(opcode) ||
           ImmediateInstr::isValidOpcode(opcode);
}

std::unique_ptr<Mnemonic>
parseSymbolInstr(std::string const &opcode,
                 std::vector<std::string> const &operands) {
    if (operands.size() != 1) {
        throw ParseExn("Symbol instruction must take 1 operand, got " +
                       std::to_string(operands.size()));
    }

    Symbol s = Symbol::parse(operands[0]);
    if (DirectInstr::isValidOpcode(opcode)) {
        return std::make_unique<DirectInstr>(opcode, s);
    } else if (ImmediateInstr::isValidOpcode(opcode)) {
        return std::make_unique<ImmediateInstr>(opcode, s);
    }
    throw ParseExn("Unknown symbol instruction opcode " + opcode);
}