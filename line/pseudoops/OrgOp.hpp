#pragma once

#include <string>
#include <vector>
#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"

/**
 * OrgOp is a pseudo-op that updates the current program address.
 */
class OrgOp : PseudoOp {
public:
    /**
     * Construct an OrgOp with a symbol representing the desired program
     * address.
     */
    OrgOp(Symbol programAddress);

    /**
     * Apply this OrgOp to the provided context, by updating its program
     * address.
     * Throw an AddressRangeExn if the new address is out of range.
     */
    void apply(Context &c);

    /**
     * Convert an opcode and operands to an OrgOp.
     * Throw a ParseExn if the operand cannot be parsed.
     */
    static OrgOp parseOperation(std::string opcode, std::vector<std::string> const &operands);

    bool operator==(const OrgOp&) const;

private:
    Symbol programAddress;
};