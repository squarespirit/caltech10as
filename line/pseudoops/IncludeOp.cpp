#include "IncludeOp.hpp"

#include <stdexcept>
#include "exceptions/ParseExn.hpp"

IncludeOp::IncludeOp(std::string f) : filename(f) {
}

void IncludeOp::apply(Context &c) {
    throw std::logic_error(".include should not be applied to a context");
}

std::unique_ptr<IncludeOp> IncludeOp::parseOp(std::string opcode, std::vector<std::string> const &operands) {
    if (opcode != ".include") {
        throw ParseExn(".include opcode was " + opcode);
    }
    if (operands.size() != 1) {
        throw ParseExn(".include must have 1 operand (got " + std::to_string(operands.size()) + ")");
    }
    return std::make_unique<IncludeOp>(operands[0]);
}

bool IncludeOp::operator==(const IncludeOp &other) const {
    return filename == other.filename;
}