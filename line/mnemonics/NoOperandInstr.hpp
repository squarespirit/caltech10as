#include "Mnemonic.hpp"

/**
 * NoOperandInstr is an instruction that takes no operands.
 */
class NoOperandInstr : public Mnemonic {
public:
    /**
     * Construct a NoOperandInstr with the given opcode.
     */
    explicit NoOperandInstr(std::string const &opcode);

    /**
     * Return whether the given string is a valid opcode for a NoOperandInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Convert an opcode and operands to a NoOperandInstr. Throw a ParseExn if 
     * the conversion fails.
     */
    static std::unique_ptr<NoOperandInstr> parseOp(std::string const &opcode,
        std::vector<std::string> const &operands);

    /**
     * Return the machine code of this NoOperandInstr.
     */
    uint16_t encode(Context const &c);

    // Inherit operator==
};
