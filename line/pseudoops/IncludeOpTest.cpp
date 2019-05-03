#include "test/catch.hpp"

#include "IncludeOp.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test IncludeOp parse") {
    std::vector<std::tuple<std::string, std::vector<std::string>, std::string>> good = {
        {".include",  {"my_filenaMe.asm"}, "my_filenaMe.asm"},
    };
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(
            *IncludeOp::parseOp(std::get<0>(good[i]), std::get<1>(good[i]))
            == IncludeOp(std::get<2>(good[i]))
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        {".include ",   {"123"}}, // Bad opcode
        {".include",    {}}, // Wrong # operands
        {".include",    {"file", "name"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(IncludeOp::parseOp(bad[i].first, bad[i].second), ParseExn);
    }
}