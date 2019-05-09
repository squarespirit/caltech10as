#pragma once
#include "Mnemonic.hpp"
#include "datatypes/Symbol.hpp"

/**
 * DirectInstr is an instruction that takes an address in data memory.
 */
class DirectInstr : public Mnemonic {
public:
    /**
     * Construct a DirectInstr with the given opcode and address operand.
     */
    DirectInstr(std::string const &opcode, Symbol const &dataAddress);

    /**
     * Return whether the opcode is a valid opcode for a DirectInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Return the machine code of this DirectInstr.
     * Throw a RangeExn if the data address is out of range.
     */
    uint16_t encode(Context const &c) const;

    bool operator==(DirectInstr const &) const;

private:
    Symbol dataAddress;
};