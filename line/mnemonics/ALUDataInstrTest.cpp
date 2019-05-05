#include "ALUDataInstr.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"
#include "test/catch.hpp"
#include <iostream>
#include <tuple>

TEST_CASE("Test ALUDataInstr parse") {
    std::vector<std::tuple<std::string, std::vector<std::string>, ALUDataInstr>>
        good = {
            // Direct, number
            {"ADC", {"2A"}, {"ADC", Symbol(Number(0x2A))}},
            // Direct, name
            {"ADD", {"$var"}, {"ADD", Symbol(Name("var"))}},
            // X-indexed, number
            {"AND", {"X,1b"}, {"AND", Register::X, Symbol(Number(0x1B))}},
            // X-indexed, name
            {"AND", {"X,$xoff"}, {"AND", Register::X, Symbol(Name("xoff"))}},
            // S-indexed, number
            {"SBB", {"S,0"}, {"SBB", Register::S, Symbol(Number(0))}},
            // S-indexed, name
            {"TST", {"S,$_S_"}, {"TST", Register::S, Symbol(Name("_S_"))}},
        };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(*ALUDataInstr::parseOp(std::get<0>(good[i]),
                                       std::get<1>(good[i])) ==
                std::get<2>(good[i]));
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        // Invalid opcode
        {"", {"A"}},
        {"or", {"A"}},
        // Wrong # operands
        {"ADD", {}},
        {"ADC", {"2A", "$var"}},
        // Malformed register
        {"CMP", {",2A"}},
        {"CMP", {"xs,FF"}},
        // Malformed symbol
        {"OR", {"S,"}},
        {"SUB", {"X,,FF"}},
        {"SUB", {"X,,$badn@m"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(
            ALUDataInstr::parseOp(std::get<0>(bad[i]), std::get<1>(bad[i])),
            ParseExn);
    }
}

TEST_CASE("Test ALUDataInstr encode") {
    Context c;
    c.addConstant(Name("const1"), Number(0xC1));
    c.addConstant(Name("const2"), Number(0x22));
    c.addConstant(Name("biG"), Number(DATA_ADDRESS_SIZE));

    std::vector<std::pair<ALUDataInstr, uint16_t>> good = {
        // Direct, number
        {{"AND", Symbol(Number(0xBC))}, 0x44BC},
        // Direct, name
        {{"CMP", Symbol(Name("const1"))}, 0x30C1},

        // X-indexed
        {{"OR", Register::X, Symbol(Name("const2"))}, 0x7522},
        // S-indexed
        {{"XOR", Register::S, Symbol(Number(1))}, 0x3601},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(std::get<0>(good[i]).encode(c) == std::get<1>(good[i]));
    }

    std::vector<ALUDataInstr> badRange = {
        // Name too large
        {"SUB", Register::S, Symbol(Name("biG"))},
        // Number too large
        {"XOR", Register::S, Symbol(Number(0xFFF))},
    };
    for (size_t i = 0; i < badRange.size(); i++) {
        REQUIRE_THROWS_AS(badRange[i].encode(c), RangeExn);
    }

    std::vector<ALUDataInstr> badName = {
        {"TST", Symbol(Name("myName"))},
        {"ADD", Register::X, Symbol(Name("___"))},
    };
    for (size_t i = 0; i < badName.size(); i++) {
        REQUIRE_THROWS_AS(badName[i].encode(c), NameExn);
    }
}