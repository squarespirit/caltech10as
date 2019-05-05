#include "Mnemonic.hpp"

/**
 * UnconditionalJumpInstrs and ConditionalJumpInstrs both take a single
 * label as an operand. This function parses both of them.
 * Throw a ParseExn if the opcode or operands are invalid.
 */
std::unique_ptr<Mnemonic>
parseLabelInstr(std::string const &opcode,
                std::vector<std::string> const &operands);

/**
 * Return whether the given opcode is one that can be parsed by
 * parseLabelInstr.
 */
bool isValidLabelOpcode(std::string const &opcode);
