#include "IncDecRegister.hpp"
#include "test/catch.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test IncDecRegister parse") {
    std::vector<std::pair<std::string, IncDecRegister>> good = {
        {"X",   IncDecRegister(Register::X)},
        {"S",   IncDecRegister(Register::S)},
        //                    isDec  isPost
        {"+X",  {Register::X, false, false}},
        {"-X",  {Register::X, true,  false}},
        {"+S",  {Register::S, false, false}},
        {"-S",  {Register::S, true,  false}},
        {"X+",  {Register::X, false, true}},
        {"X-",  {Register::X, true,  true}},
        {"S+",  {Register::S, false, true}},
        {"S-",  {Register::S, true,  true}}
    };

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(IncDecRegister::parse(good[i].first) == good[i].second);
    }

    std::vector<std::string> bad = {
        "",
        // Bad single register
        "x",
        // Bad +/-
        "/X",
        "*S",
        "X^",
        "S$",
        "X++",
        // No register
        "++",
        "--",
        // Bad register
        "XX"
        "SS",
        "XS",
        "SX+"
        "+R",
        "-T"
        "u+"
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(IncDecRegister::parse(bad[i]), ParseExn);
    }
}