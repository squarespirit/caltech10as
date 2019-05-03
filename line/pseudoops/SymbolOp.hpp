#include "../Operation.hpp"
#include <vector>
#include <memory>
#include "PseudoOp.hpp"

/**
 * Many pseudo-ops have only one operand, which is a symbol.
 * parseSymbolOperation function parses all of them.
 * It returns a newly-allocated PseudoOp.
 * Throw ParseExn if the operation cannot be parsed.
 */
std::unique_ptr<PseudoOp> parseSymbolOp(std::string opcode, std::vector<std::string> const &operands);