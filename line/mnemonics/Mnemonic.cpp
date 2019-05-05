#include "Mnemonic.hpp"
#include "ALUDataInstr.hpp"
#include "IndexedLoadStoreInstr.hpp"
#include "LabelInstr.hpp"
#include "NoOperandInstr.hpp"
#include "SymbolInstr.hpp"
#include "exceptions/ParseExn.hpp"

Mnemonic::Mnemonic(std::string const &opcode) : opcode(opcode) {}

std::unique_ptr<Mnemonic>
Mnemonic::parseOp(std::string const &opcode,
                  std::vector<std::string> const &operands) {
    if (ALUDataInstr::isValidOpcode(opcode)) {
        return ALUDataInstr::parseOp(opcode, operands);
    }
    if (IndexedLoadStoreInstr::isValidOpcode(opcode)) {
        return IndexedLoadStoreInstr::parseOp(opcode, operands);
    }
    if (isValidLabelOpcode(opcode)) {
        return parseLabelInstr(opcode, operands);
    }
    if (NoOperandInstr::isValidOpcode(opcode)) {
        return NoOperandInstr::parseOp(opcode, operands);
    }
    if (isValidSymbolInstrOpcode(opcode)) {
        return parseSymbolInstr(opcode, operands);
    }
    throw ParseExn("Unknown mnemonic " + opcode);
}

bool Mnemonic::operator==(const Mnemonic &other) const {
    return opcode == other.opcode;
}

std::string Mnemonic::getOpcode() { return opcode; }
