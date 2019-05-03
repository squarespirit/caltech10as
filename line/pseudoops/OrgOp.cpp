#include "OrgOp.hpp"
#include <limits>
#include "exceptions/RangeExn.hpp"
#include "exceptions/ParseExn.hpp"

OrgOp::OrgOp(Symbol programAddress) : programAddress(programAddress) {
}

void OrgOp::apply(Context &c) {
    c.setCurProgramAddress(programAddress.resolve(c));
}

bool OrgOp::operator==(const OrgOp &other) const {
    return programAddress == other.programAddress;
}