#pragma once
#include "Mnemonic.hpp"

/**
 * Parse an instruction which takes a single Symbol as an operand.
 * This parses both DirectInstrs and ImmediateInstrs.
 * Throw a ParseExn if the opcode or operands are invalid.
 */
std::unique_ptr<Mnemonic>
parseSymbolInstr(std::string const &opcode,
                 std::vector<std::string> const &operands);

/**
 * Return whether the given opcode is one that can be parsed by
 * parseSymbolInstr.
 */
bool isValidSymbolInstrOpcode(std::string const &opcode);