#include "test/catch.hpp"

#include "ConstOp.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "context/Context.hpp"

TEST_CASE("Test ConstOp apply") {
    Context c;
    c.addConstant(Name("const1"), Number(0x10));

    // Good name
    ConstOp(Name("const2"), Number(0x20)).apply(c);
    REQUIRE(c.lookupConstant(Name("const1")) == Number(0x10));
    REQUIRE(c.lookupConstant(Name("const2")) == Number(0x20));

    // Name already exists
    REQUIRE_THROWS_AS(
        ConstOp(Name("const2"), Number(0x30)).apply(c),
        NameExn
    );
}

TEST_CASE("Test ConstOp parse") {
    std::vector<std::tuple<std::string, std::vector<std::string>, Name, Number>> good = {
        {".const",  {"_myvar", "123"},  Name("_myvar"), Number("123")},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(
            *ConstOp::parseOp(std::get<0>(good[i]), std::get<1>(good[i]))
            == ConstOp(std::get<2>(good[i]), std::get<3>(good[i]))
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        {" .const",  {"123"}}, // Bad opcode
        {".const",  {}}, // Wrong # operands
        {".const",  {"a", "1", "c"}},
        {".const",  {"$name", "123"}}, // Bad name
        {".const",  {"var", "222n"}}, // Bad number
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(ConstOp::parseOp(bad[i].first, bad[i].second), ParseExn);
    }
}