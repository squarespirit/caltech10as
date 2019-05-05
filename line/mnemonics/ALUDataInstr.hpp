#include "Mnemonic.hpp"
#include "datatypes/Register.hpp"
#include "datatypes/Symbol.hpp"

/**
 * ALUDataInstr is an ALU instruction that reads from data memory. It can
 * take either a direct address or a register and offset as an operand.
 */
class ALUDataInstr : public Mnemonic {
public:
    /**
     * Construct an ALU instruction with direct addressing.
     * da is the address.
     */
    ALUDataInstr(std::string const &opcode, Symbol const &da);

    /**
     * Construct an ALU instruction with indexed addressing.
     * reg is the register to index from.
     * da is the data offset.
     */
    ALUDataInstr(std::string const &opcode, Register const &reg,
                 Symbol const &da);

    /**
     * Return whether the opcode is a valid opcode for an ALUDataInstr.
     */
    static bool isValidOpcode(std::string const &opcode);

    /**
     * Parse an ALUDataInstr. Throw a ParseExn if the opcode and operands
     * cannot be parsed.
     */
    static std::unique_ptr<ALUDataInstr>
    parseOp(std::string const &opcode,
            std::vector<std::string> const &operands);

    /**
     * Return the machine code of this ALUDataInstr.
     * Throw a RangeExn if the data address/offset is out of range.
     */
    uint16_t encode(Context const &c);

    bool operator==(ALUDataInstr const &) const;

private:
    std::optional<Register> reg;
    Symbol dataAddress;
};
