#include "test/catch.hpp"

#include "DataOp.hpp"
#include <tuple>
#include "exceptions/RangeExn.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "context/Context.hpp"

TEST_CASE("Test DataOp parseOperation") {
    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>> good = {
        {".data",    {"123"},    Symbol(std::optional<Name>(), Number(0x123))},
        {".data",    {"$red"},   Symbol(Name("red"), std::optional<Number>())},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(
            DataOp::parseOperation(std::get<0>(good[i]), std::get<1>(good[i]))
            == DataOp(std::get<2>(good[i]))
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        {"data",    {"123"}}, // Bad opcode
        {".data",   {}}, // Wrong # operands
        {".data",   {"a", "b"}},
        {".data",   {"", "", ""}},
        {".data",   {"FFGF"}}, // Bad symbol
        {".data",   {"$r#d"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(DataOp::parseOperation(bad[i].first, bad[i].second), ParseExn);
    }
}

TEST_CASE("Test DataOp apply") {
    Context c;
    c.setCurDataAddress((number_t) 0x5);
    c.addConstant(Name("const1"), Number(0x10));
    c.addConstant(Name("big"), Number(0xFFFF));
    
    // Good symbol
    // Good number
    DataOp(Symbol(std::optional<Name>(), Number(0x15))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x15);
    // Good name
    DataOp(Symbol(Name("const1"), std::optional<Number>())).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x10);

    // Bad name
    REQUIRE_THROWS_AS(
        DataOp(Symbol(Name("const2"), std::optional<Number>())).apply(c),
        NameExn
    );
    // Number too large
    REQUIRE_THROWS_AS(
        DataOp(Symbol(std::optional<Name>(), Number(0xABC))).apply(c),
        RangeExn
    );
    // Name maps to number that is too large
    REQUIRE_THROWS_AS(
        DataOp(Symbol(Name("big"), std::optional<Number>())).apply(c),
        RangeExn
    );
}