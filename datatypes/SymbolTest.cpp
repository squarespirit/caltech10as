#include "test/catch.hpp"

#include "Number.hpp"
#include "Symbol.hpp"
#include "context/Context.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test Symbol parsing") {
    std::vector<std::pair<std::string, number_t>> numbers = {
        {"0", 0}, {"a12", 0xa12}, {"FFFF", 0xFFFF}};
    for (size_t i = 0; i < numbers.size(); i++) {
        REQUIRE(Symbol::parse(numbers[i].first) ==
                Symbol(Number(numbers[i].second)));
    }

    std::vector<std::pair<std::string, std::string>> names = {
        {"$a", "a"}, {"$FFFF", "FFFF"}, {"$_myName", "_myName"}};
    for (size_t i = 0; i < numbers.size(); i++) {
        REQUIRE(Symbol::parse(names[i].first) == Symbol(Name(names[i].second)));
    }

    std::vector<std::string> bad = {"",      // Empty symbol
                                    "FFFFG", // Invalid number
                                    "$",     // Invalid name
                                    "$n@me", "$hello "};
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(Symbol::parse(bad[i]), ParseExn);
    }
}

TEST_CASE("Test Symbol resolve") {
    Context c;
    c.addLabel(Name("lab1"), Number(1));
    c.addConstant(Name("const1"), Number(2));

    // Literal number
    REQUIRE(Symbol(Number(123)).resolve(c) == 123);

    // Constant exists
    REQUIRE(Symbol(Name("const1")).resolve(c) == 2);

    // Constant does not exist
    REQUIRE_THROWS_AS(Symbol(Name("hello")).resolve(c), NameExn);
}
