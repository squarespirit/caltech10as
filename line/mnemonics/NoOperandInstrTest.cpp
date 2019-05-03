#include "test/catch.hpp"
#include "NoOperandInstr.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test NoOperandInstr parseOp") {
    // Good
    REQUIRE(*NoOperandInstr::parseOp("NOP", {}) == NoOperandInstr("NOP"));
    REQUIRE(*NoOperandInstr::parseOp("INC", {}) == NoOperandInstr("INC"));
    REQUIRE(*NoOperandInstr::parseOp("PUSHF", {}) == NoOperandInstr("PUSHF"));

    // Bad
    // Bad opcode
    REQUIRE_THROWS_AS(*NoOperandInstr::parseOp("PUSH", {}), ParseExn);
    REQUIRE_THROWS_AS(*NoOperandInstr::parseOp(" NOP", {}), ParseExn);
    // Bad # operands
    REQUIRE_THROWS_AS(*NoOperandInstr::parseOp("INC", {""}), ParseExn);
    REQUIRE_THROWS_AS(*NoOperandInstr::parseOp("DEC", {"1", "2"}), ParseExn);
}

TEST_CASE("Test NoOperandInstr encode") {
    Context c;

    // Only good cases
    // One of each type of instruction
    REQUIRE(NoOperandInstr("NEG").encode(c) == 0x2700);
    REQUIRE(NoOperandInstr("STI").encode(c) == 0x7F81);
    REQUIRE(NoOperandInstr("TSA").encode(c) == 0x6700);    
    REQUIRE(NoOperandInstr("POPF").encode(c) == 0x0200);
    REQUIRE(NoOperandInstr("NOP").encode(c) == 0x1F80);
}