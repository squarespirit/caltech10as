#include "DirectInstr.hpp"
#include "exceptions/RangeExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test DirectInstr encode") {
    Context c;
    c.addConstant(Name("const1"), Number(0xC1));
    c.addConstant(Name("const2"), Number(DATA_ADDRESS_SIZE - 1));
    c.addConstant(Name("biG"), Number(DATA_ADDRESS_SIZE));

    std::vector<std::pair<DirectInstr, uint16_t>> good = {
        // Number
        {{"LDD", Symbol(Number(0xAD))}, 0x80AD},
        {{"STD", Symbol(Number(DATA_ADDRESS_SIZE - 1))}, 0xA0FF},
        // Name
        {{"IN", Symbol(Name("const1"))}, 0x90C1},
        {{"OUT", Symbol(Name("const2"))}, 0xB0FF},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(std::get<0>(good[i]).encode(c) == std::get<1>(good[i]));
    }

    std::vector<DirectInstr> badRange = {
        // Name too large
        {"LDD", Symbol(Name("biG"))},
        // Number too large
        {"IN", Symbol(Number(0xFFF))},
    };
    for (size_t i = 0; i < badRange.size(); i++) {
        REQUIRE_THROWS_AS(badRange[i].encode(c), RangeExn);
    }
}