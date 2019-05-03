#include "SymbolOp.hpp"

#include <stdexcept>
#include <unordered_set>
#include "datatypes/Symbol.hpp"
#include "exceptions/ParseExn.hpp"
#include "DataOp.hpp"
#include "OrgOp.hpp"
#include "ByteOp.hpp"

const std::unordered_set<std::string> symbolOpcodes = {".byte", ".data", ".org"};

bool isValidSymbolOpcode(std::string opcode) {
    return symbolOpcodes.find(opcode) != symbolOpcodes.end();
}


std::unique_ptr<PseudoOp> parseSymbolOp(std::string opcode, std::vector<std::string> const &operands) {
    if (!isValidSymbolOpcode(opcode)) {
        throw ParseExn("Unknown pseudo-op with symbol operand " + opcode);
    }

    if (operands.size() != 1) {
        throw ParseExn(opcode + " must have one operand (got " + std::to_string(operands.size()) + ")");
    }

    Symbol s = Symbol::parse(operands[0]);

    if (opcode == ".byte") {
        return std::unique_ptr<PseudoOp>(new ByteOp(s));
    } else if (opcode == ".data") {
        return std::unique_ptr<PseudoOp>(new DataOp(s));
    } else if (opcode == ".org") {
        return std::unique_ptr<PseudoOp>(new OrgOp(s));
    }
    throw std::logic_error("Missing case for opcode " + opcode);
}