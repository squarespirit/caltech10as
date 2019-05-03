#pragma once

#include <string>
#include <vector>
#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"

/**
 * DataOp is a pseudo-op that updates the current data address.
 */
class DataOp : PseudoOp {
public:
    /**
     * Construct a DataOp with the desired data address.
     */
    DataOp(Symbol da);

    /**
     * Apply this DataOp to the provided context, by updating the data
     * address.
     * Throw an RangeExn if the new address is out of range.
     */
    void apply(Context &c);

    /**
     * Convert an opcode and operands to a DataOp.
     * Throw a ParseExn if the operand cannot be parsed.
     */
    static DataOp parseOperation(std::string opcode, std::vector<std::string> const &operands);

    bool operator==(const DataOp&) const;

private:
    Symbol dataAddress;
};