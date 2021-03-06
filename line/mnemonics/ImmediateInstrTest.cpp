#include "ImmediateInstr.hpp"
#include "exceptions/RangeExn.hpp"
#include "test/catch.hpp"
#include <iostream>

TEST_CASE("Test ImmediateInstr encode") {
    Context c;
    c.addConstant(Name("const1"), Number(0xC1));
    c.addConstant(Name("const2"), Number(0x22));
    c.addConstant(Name("biG"), Number(DATA_VALUE_SIZE));

    std::vector<std::pair<ImmediateInstr, uint16_t>> good = {
        // Number
        {{"ANDI", Symbol(Number(0xBC))}, 0x47BC},
        {{"LDI", Symbol(Number(DATA_VALUE_SIZE - 1))}, 0x89FF},
        // Name
        {{"CMPI", Symbol(Name("const1"))}, 0x33C1},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(std::get<0>(good[i]).encode(c) == std::get<1>(good[i]));
    }

    std::vector<ImmediateInstr> badRange = {
        // Name too large
        {"SUBI", Symbol(Name("biG"))},
        // Number too large
        {"ORI", Symbol(Number(0xFFF))},
    };
    for (size_t i = 0; i < badRange.size(); i++) {
        REQUIRE_THROWS_AS(badRange[i].encode(c), RangeExn);
    }
}