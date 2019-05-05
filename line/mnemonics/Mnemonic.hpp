#pragma once

#include "../Operation.hpp"
#include "context/Context.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * Mnemonic is an instruction that can be translated to machine code.
 */
class Mnemonic : public Operation {
public:
    /**
     * Construct a mnemonic with the given opcode. (Subclasses should have
     * more data members.)
     */
    explicit Mnemonic(std::string const &opcode);

    /**
     * Convert an opcode and operands to a Mnemonic. Throw a ParseExn if
     * the conversion fails.
     */
    static std::unique_ptr<Mnemonic>
    parseOp(std::string const &opcode,
            std::vector<std::string> const &operands);

    /**
     * Convert this mnemonic to machine code.
     */
    virtual uint16_t encode(Context const &c) = 0;

    /**
     * Return true if their opcodes are equal.
     */
    bool operator==(const Mnemonic &) const;

    /**
     * Get the mnemonic's opcode.
     */
    std::string getOpcode();

private:
    std::string opcode;
};