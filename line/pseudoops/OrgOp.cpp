#include "OrgOp.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"
#include <limits>

OrgOp::OrgOp(Symbol const &programAddress) : programAddress(programAddress) {}

void OrgOp::apply(Context &c) {
    c.setCurProgramAddress(programAddress.resolve(c));
}

bool OrgOp::operator==(const OrgOp &other) const {
    return programAddress == other.programAddress;
}