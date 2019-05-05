#include "Mnemonic.hpp"

/**
 * UnconditionalJumpInstr is either CALL or JMP.
 * The absolute address of the jump destination is in the machine code.
 */
class UnconditionalJumpInstr : public Mnemonic {
public:
    /**
     * Construct an UnconditionalJumpInstr.
     * name is the name of the label to jump to.
     */
    UnconditionalJumpInstr(std::string const &opcode, Name const &name);

    /**
     * Return whether the given string is a valid opcode for an
     * UnconditionalJumpInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Return the machine code of this UnconditionalJumpInstr.
     * Throw RangeExn if the label is out of range.
     * (Should not happen for user-defined labels).
     */
    uint16_t encode(Context const &c);

    bool operator==(const UnconditionalJumpInstr &other) const;

private:
    Name label;
};
