#pragma once
#include "Mnemonic.hpp"
#include "datatypes/IncDecRegister.hpp"
#include "datatypes/Symbol.hpp"

/**
 * An IndexedLoadStoreInstr reads/writes to data memory at a given offset
 * from a given register.
 * The register can be pre/post incremented/decremented.
 */
class IndexedLoadStoreInstr : public Mnemonic {
public:
    /**
     * Construct an IndexedLoadStoreInstr.
     * incDecReg is the register to use, and whether to increment/decrement.
     * dataOffset is the offset.
     */
    IndexedLoadStoreInstr(std::string const &opcode,
        IncDecRegister const &incDecReg, Symbol const &dataOffset);
    
    /**
     * Parse an IndexedLoadStoreInstr.
     * Throw ParseExn if the instruction cannot be parsed.
     */
    static std::unique_ptr<IndexedLoadStoreInstr> parseOp(
        std::string const &opcode, std::vector<std::string> const &operands);

    /**
     * Return whether the opcode is a valid opcode for an IndexedLoadStoreInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Convert this instruction into machine code.
     * Throw RangeExn if the offset is too large.
     */
    uint16_t encode(Context const &c) override;

    bool operator==(const IndexedLoadStoreInstr&) const;

private:
    IncDecRegister incDecReg;
    Symbol dataOffset;
};