#include "Mnemonic.hpp"

/**
 * A ConditionalJumpInstr jumps to a label based on a condition.
 * The relative address of the label is stored in the low 8 bits of the
 * instruction.
 */
class ConditionalJumpInstr : public Mnemonic {
public:
    ConditionalJumpInstr(std::string const &opcode, Name const &label);

    static bool isValidOpcode(std::string const &opcode);

    /**
     * Convert this instruction into machine code.
     * Throw RangeExn if the label is too far away.
     */
    uint16_t encode(Context const &c) const override;

    bool operator==(const ConditionalJumpInstr &) const;

private:
    Name label;
};