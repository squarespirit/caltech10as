#include "../Operation.hpp"
#include "PseudoOp.hpp"
#include <memory>
#include <vector>

/**
 * Return if the given opcode is of an operation that can be parsed by
 * parseSymbolOp.
 */
bool isValidSymbolOpcode(std::string const &opcode);

/**
 * Many pseudo-ops have only one operand, which is a symbol.
 * parseSymbolOperation function parses all of them.
 * It returns a newly-allocated PseudoOp.
 * Throw ParseExn if the operation cannot be parsed.
 */
std::unique_ptr<PseudoOp>
parseSymbolOp(std::string const &opcode,
              std::vector<std::string> const &operands);