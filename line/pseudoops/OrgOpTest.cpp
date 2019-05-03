#include "test/catch.hpp"

#include "OrgOp.hpp"
#include <tuple>
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"
#include "context/Context.hpp"

TEST_CASE("Test OrgOp parseOperation") {
    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>> good = {
        {".org",    {"123"},    Symbol(std::optional<Name>(), Number(0x123))},
        {".org",    {"$red"},   Symbol(Name("red"), std::optional<Number>())},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(
            OrgOp::parseOperation(std::get<0>(good[i]), std::get<1>(good[i]))
            == OrgOp(std::get<2>(good[i]))
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        {"org",     {"123"}}, // Bad opcode
        {".org",    {}}, // Wrong # operands
        {".org",    {"a", "b"}},
        {".org",    {"", "", ""}},
        {".org",    {"FFGF"}}, // Bad symbol
        {".org",    {"$r#d"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(OrgOp::parseOperation(bad[i].first, bad[i].second), ParseExn);
    }
}

TEST_CASE("Test OrgOp apply") {
    Context c;
    c.setCurProgramAddress(0x5);
    c.addConstant(Name("const1"), Number(0x10));
    
    // Good symbol
    // Good number
    OrgOp(Symbol(std::optional<Name>(), Number(0x15))).apply(c);
    REQUIRE(c.getCurProgramAddress() == 0x15);
    // Good name
    OrgOp(Symbol(Name("const1"), std::optional<Number>())).apply(c);
    REQUIRE(c.getCurProgramAddress() == 0x10);

    // Bad name
    REQUIRE_THROWS_AS(
        OrgOp(Symbol(Name("const2"), std::optional<Number>())).apply(c),
        NameExn
    );
    // Number too large
    REQUIRE_THROWS_AS(
        OrgOp(Symbol(std::optional<Name>(), Number(0x2FFF))).apply(c),
        RangeExn
    );
}