#pragma once
#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"
#include <vector>
#include <memory>

/**
 * ConstOp defines a constant with a given value.
 */
class ConstOp : PseudoOp {
public:
    /**
     * Construct a ConstOp with the given name and value.
     */
    ConstOp(Name name, Number number);

    /**
     * Apply this ConstOp to the provided context.
     * Add a constant of the given name to the context.
     * Throw a NameExn if the name already exists.
     */
    void apply(Context &c);

    /**
     * Convert the given opcode and operands to a ConstOp.
     * The format is .const <name> <number>.
     * Throw a ParseExn if the operation cannot be converted.
     */
    static std::unique_ptr<ConstOp> parseOp(std::string opcode, std::vector<std::string> const &operands);

    bool operator==(const ConstOp&) const;

private:
    Name name;
    Number number;
};