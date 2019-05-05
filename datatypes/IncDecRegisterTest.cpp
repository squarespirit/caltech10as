#include "IncDecRegister.hpp"
#include "test/catch.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test IncDecRegister parse") {
    std::vector<std::pair<std::string, IncDecRegister>> good = {
        {"X",   IncDecRegister(Register(true))},
        {"S",   IncDecRegister(Register(false))},
        //                        isDec  isPost
        {"+X",  {Register(true),  false, false}},
        {"-X",  {Register(true),  true,  false}},
        {"+S",  {Register(false), false, false}},
        {"-S",  {Register(false), true,  false}},
        {"X+",  {Register(true),  false, true}},
        {"X-",  {Register(true),  true,  true}},
        {"S+",  {Register(false), false, true}},
        {"S-",  {Register(false), true,  true}}
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