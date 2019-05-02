#pragma once

#include <string>
#include <vector>
#include "../Operation.hpp"
#include "context/Context.hpp"

/**
 * PseudoOp is a directive to the assembler.
 */
class PseudoOp : Operation {
public:
    /**
     * Convert an opcode and operands to a PseudoOp. Throw a ParseExn if 
     * the conversion fails.
     */
    static Operation parseOperation(std::string opcode, std::vector<std::string> const &operands);

    /**
     * Apply this PseudoOp to the provided context. 
     */
    virtual void apply(Context &c) = 0;
};