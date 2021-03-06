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
    ImmediateInstr(std::string const &, Symbol const &);

    /**
     * Return whether the opcode is a valid opcode for an ImmediateInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Return the machine code of this ImmediateInstr.
     * Throw a RangeExn if the data value is out of range.
     */
    uint16_t encode(Context const &c) const;

    bool operator==(ImmediateInstr const &) const;

private:
    Symbol dataValue;
};