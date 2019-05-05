#pragma once

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
    static Operation parse(std::string);
};