#include "OrgOp.hpp"
#include <limits>
#include "datatypes/Addresses.hpp"
#include "exceptions/RangeExn.hpp"
#include "exceptions/ParseExn.hpp"

OrgOp::OrgOp(Symbol programAddress) : programAddress(programAddress) {
}

void OrgOp::apply(Context &c) {
    number_t n = programAddress.resolve(c);
    if (n < std::numeric_limits<program_address_t>::min() 
            || n > std::numeric_limits<program_address_t>::max()) {
        throw RangeExn(".org address " + std::to_string(n) + " is outside program address space");
    }
    c.setCurProgramAddress(n);
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