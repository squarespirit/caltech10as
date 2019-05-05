#pragma once

#include <memory>
#include <string>

/**
 * Operation is a general operation. It can be a mnemonic for an instruction
 * or a pseudo-op.
 */
class Operation {
public:
    /**
     * Convert a string to an Operation. Throw a ParseExn if the string
     * cannot be converted.
     */
    static std::unique_ptr<Operation> parse(std::string const &);

    /**
     * Make Operation dynamically castable, by adding a vtable.
     * The easiest way to do this is to mark the destructor as virtual.
     */
    virtual ~Operation() = 0;
};