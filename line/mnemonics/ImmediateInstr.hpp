#include "Mnemonic.hpp"
#include "datatypes/Symbol.hpp"

/**
 * ImmediateInstr is an instruction that takes an immediate data value.
 */
class ImmediateInstr : public Mnemonic {
public:
    /**
     * Construct an ImmediateInstr with the given opcode and the given
     * symbol as the data value.
     */
    ImmediateInstr(std::string, Symbol);

    /**
     * Return whether the opcode is a valid opcode for an ImmediateInstr.
     */
    static bool isValidOpcode(std::string opcode);

    /**
     * Return the machine code of this ALUDataInstr.
     * Throw a RangeExn if the data address/offset is out of range.
     */
    uint16_t encode(Context const &c);

    bool operator==(ImmediateInstr const &) const;

private:
    Symbol dataValue;
};