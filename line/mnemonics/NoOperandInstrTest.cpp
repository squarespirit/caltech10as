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
    std::vector<std::pair<std::string, uint16_t>> good = {
        // One of each type of instruction
        {"NEG", 0x2700},
        {"STI", 0x7F81},
        {"TSA", 0x6700},
        {"POPF", 0x0200},
        {"NOP", 0x1F80}
    };

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(NoOperandInstr(good[i].first).encode(c) == good[i].second);
    }
}