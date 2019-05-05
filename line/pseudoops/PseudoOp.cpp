#include "PseudoOp.hpp"
#include "ConstOp.hpp"
#include "IncludeOp.hpp"
#include "SymbolOp.hpp"
#include "exceptions/ParseExn.hpp"

std::unique_ptr<PseudoOp>
PseudoOp::parseOp(std::string opcode,
                  std::vector<std::string> const &operands) {
    if (isValidSymbolOpcode(opcode)) {
        return parseSymbolOp(opcode, operands);
    } else if (opcode == ".const") {
        return std::unique_ptr<PseudoOp>(ConstOp::parseOp(opcode, operands));
    } else if (opcode == ".include") {
        return std::unique_ptr<PseudoOp>(IncludeOp::parseOp(opcode, operands));
    }
    throw ParseExn("Unknown pseudo-op " + opcode);
}
