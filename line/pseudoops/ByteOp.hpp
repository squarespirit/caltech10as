#pragma once

#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"

/**
 * ByteOp writes the byte at the current data address.
 */
class ByteOp : public PseudoOp {
public:
    /**
     * Construct a ByteOp with the value to write.
     */
    explicit ByteOp(Symbol const &val);

    /**
     * Apply this ByteOp to the provided context.
     * Currently, there is no means to actually write a byte to data memory.
     * So, just advance the data address.
     * Throw a RangeExn if the value to write is out of range.
     */
    void apply(Context &c) const override;

    bool operator==(ByteOp const &) const;

private:
    Symbol dataValue;
};
