#include "Operation.hpp"
#include "datatypes/Whitespace.hpp"
#include "exceptions/ParseExn.hpp"
#include "mnemonics/Mnemonic.hpp"
#include "pseudoops/PseudoOp.hpp"

std::unique_ptr<Operation> Operation::parse(std::string const &s) {
    std::vector<std::string> tokens = splitWhitespace(s);
    if (tokens.empty()) {
        throw ParseExn("No tokens in operation");
    }
    // TODO make more efficient...
    std::string opcode = tokens[0];
    tokens.erase(tokens.begin());
    // The tokens are now the operands
    std::vector<std::string> &operands = tokens;

    if (opcode.empty()) {
        throw ParseExn("Empty opcode");
    }

    if (opcode[0] == '.') { // Pseudo-op
        return std::unique_ptr<Operation>(PseudoOp::parseOp(opcode, operands));
    }
    // Mnemonic
    return std::unique_ptr<Operation>(Mnemonic::parseOp(opcode, operands));
}

Operation::~Operation() {}
