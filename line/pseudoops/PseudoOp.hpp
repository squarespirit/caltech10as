#pragma once

#include "../Operation.hpp"
#include "context/Context.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * PseudoOp is a directive to the assembler.
 */
class PseudoOp : public Operation {
public:
    /**
     * Convert an opcode and operands to a PseudoOp. Throw a ParseExn if
     * the conversion fails.
     */
    static std::unique_ptr<PseudoOp>
    parseOp(std::string opcode, std::vector<std::string> const &operands);

    /**
     * Apply this PseudoOp to the provided context.
     */
    virtual void apply(Context &c) const = 0;
};