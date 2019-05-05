#include "test/catch.hpp"
#include "IndexedLoadStoreInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"

TEST_CASE("Test IndexedLoadStoreInstr parse") {
    std::vector<std::tuple<std::string, std::vector<std::string>, 
                           IndexedLoadStoreInstr>> good = {
        // No inc/dec
        // Name
        {"LD", {"X,$name"},
         {"LD", IncDecRegister(Register::X), Symbol(Name("name"))}},
        // Number
        {"LD", {"S,12"}, 
         {"LD", IncDecRegister(Register::S), Symbol(Number(0x12))}},
        
        // With inc/dec
        {"ST", {"+S,$off"},
         {"ST", IncDecRegister(Register::S, false, false), Symbol(Name("off"))}},
        {"ST", {"X-,34"},
         {"ST", IncDecRegister(Register::X, true, true), Symbol(Number(0x34))}},
    };

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(
            *IndexedLoadStoreInstr::parseOp(std::get<0>(good[i]), std::get<1>(good[i]))
            == std::get<2>(good[i])
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        // Bad opcode
        {"LDD", {}},
        // Bad # operands
        {"LD", {}},
        {"LD", {"1", "2"}},
        // No regspec
        {"ST", {"FF"}},
        // No offset
        {"ST", {"+X"}},
        // Comma with nothing next to it
        {"ST", {","}},
        {"ST", {"X,"}},
        {"ST", {",,"}},
        {"LD", {"X,,FF"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(
            IndexedLoadStoreInstr::parseOp(std::get<0>(bad[i]), std::get<1>(bad[i])),
            ParseExn
        );
    }
}

TEST_CASE("Test IndexedLoadStoreInstr encode") {
    Context c;
    c.addConstant(Name("const1"), Number(0xC1));
    c.addConstant(Name("const2"), Number(0x22));
    c.addConstant(Name("biG"), Number(DATA_ADDRESS_SIZE));

    std::vector<std::pair<IndexedLoadStoreInstr, uint16_t>> good = {
        // Loads
        // X
        {{"LD", IncDecRegister(Register::X), Symbol(Name("const1"))},
         0x97C1},
        // Pre-increment X
        {{"LD", IncDecRegister(Register::X, false, false), Symbol(Number(0x20))},
         0x8620},
        // S
        {{"LD", IncDecRegister(Register::S), Symbol(Name("const2"))},
         0x9322},
        // Pre-decrement S
        {{"LD", IncDecRegister(Register::S, true, false), Symbol(Number(0x01))},
         0x8A01},
        
        // Stores
        // X
        {{"ST", IncDecRegister(Register::X), Symbol(Number(0x90))},
         0xB790},
        // Post-decrement X
        {{"ST", IncDecRegister(Register::X, true, true), Symbol(Number(0xAA))},
         0xBEAA},
        // Post-increment S
        {{"ST", IncDecRegister(Register::S, false, true), Symbol(Number(0x00))},
         0xB200}
    };

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(good[i].first.encode(c) == good[i].second);
    }

    std::vector<IndexedLoadStoreInstr> badrange = {
        // Name too big
        {"LD", IncDecRegister(Register::X), Symbol(Name("biG"))},
        // Number too big
        {"ST", IncDecRegister(Register::S, false, true), Symbol(Number(0xFFF))},
    };
    for (size_t i = 0; i < badrange.size(); i++) {
        REQUIRE_THROWS_AS(badrange[i].encode(c), RangeExn);
    }
}
