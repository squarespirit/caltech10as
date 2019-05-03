#include "SymbolOp.hpp"

#include <stdexcept>
#include "datatypes/Symbol.hpp"
#include "exceptions/ParseExn.hpp"
#include "DataOp.hpp"
#include "OrgOp.hpp"

std::unique_ptr<PseudoOp> parseSymbolOp(std::string opcode, std::vector<std::string> const &operands) {
    if (opcode != ".data" && opcode != ".org") {
        throw ParseExn("Unrecognized opcode " + opcode);
    }

    if (operands.size() != 1) {
        throw ParseExn(opcode + " must have one operand (got " + std::to_string(operands.size()) + ")");
    }

    Symbol s = Symbol::parse(operands[0]);

    if (opcode == ".data") {
        return std::unique_ptr<PseudoOp>(new DataOp(s));
    } else if (opcode == ".org") {
        return std::unique_ptr<PseudoOp>(new OrgOp(s));
    }
    throw std::logic_error("Missing case for opcode " + opcode);
}