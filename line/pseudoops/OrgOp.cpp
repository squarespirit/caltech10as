#include "OrgOp.hpp"
#include <limits>
#include "exceptions/RangeExn.hpp"
#include "exceptions/ParseExn.hpp"

OrgOp::OrgOp(Symbol programAddress) : programAddress(programAddress) {
}

void OrgOp::apply(Context &c) {
    c.setCurProgramAddress(programAddress.resolve(c));
}

OrgOp OrgOp::parseOperation(std::string opcode, std::vector<std::string> const &operands) {
    if (opcode != ".org") {
        throw ParseExn(".org opcode was " + opcode);
    }
    if (operands.size() != 1) {
        throw ParseExn(".org must have one operand (got " + std::to_string(operands.size()) + ")");
    }
    return OrgOp(Symbol::parse(operands[0]));
}

bool OrgOp::operator==(const OrgOp &other) const {
    return programAddress == other.programAddress;
}