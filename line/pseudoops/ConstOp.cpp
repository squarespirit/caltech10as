#include "ConstOp.hpp"
#include "exceptions/ParseExn.hpp"

ConstOp::ConstOp(Name name, Number number) : name(name), number(number) {
}

void ConstOp::apply(Context &c) {
    c.addConstant(name, number);
}

std::unique_ptr<ConstOp> ConstOp::parseOp(std::string opcode, std::vector<std::string> const &operands) {
    if (opcode != ".const") {
        throw ParseExn(".const opcode was " + opcode);
    }
    if (operands.size() != 2) {
        throw ParseExn(".const must have 2 operands (got " + std::to_string(operands.size()) + ")");
    }
    return std::make_unique<ConstOp>(Name(operands[0]), Number(operands[1]));
}

bool ConstOp::operator==(const ConstOp &other) const {
    return name == other.name && number == other.number;
}
