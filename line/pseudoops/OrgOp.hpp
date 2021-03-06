#pragma once

#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"
#include <string>
#include <vector>

/**
 * OrgOp is a pseudo-op that updates the current program address.
 */
class OrgOp : public PseudoOp {
public:
    /**
     * Construct an OrgOp with a symbol representing the desired program
     * address.
     */
    explicit OrgOp(Symbol const &programAddress);

    /**
     * Apply this OrgOp to the provided context, by updating its program
     * address.
     * Throw a RangeExn if the new address is out of range.
     */
    void apply(Context &c) const;

    bool operator==(const OrgOp &) const;

private:
    Symbol programAddress;
};