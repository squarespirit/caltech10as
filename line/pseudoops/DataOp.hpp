#pragma once

#include <string>
#include <vector>
#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"

/**
 * DataOp is a pseudo-op that updates the current data address.
 */
class DataOp : public PseudoOp {
public:
    /**
     * Construct a DataOp with the desired data address.
     */
    explicit DataOp(Symbol const &da);

    /**
     * Apply this DataOp to the provided context, by updating the data
     * address.
     * Throw an RangeExn if the new address is out of range.
     */
    void apply(Context &c);

    bool operator==(const DataOp&) const;

private:
    Symbol dataAddress;
};