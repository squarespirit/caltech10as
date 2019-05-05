#include "Whitespace.hpp"
#include "test/catch.hpp"

TEST_CASE("Test splitWhitespace") {
    std::vector<std::pair<std::string, std::vector<std::string>>> cases = {
        {"", {""}},
        {"a", {"a"}},
        // The whitespace "delimits" the empty string at the start and the
        // empty string at the end
        {" ", {"", ""}},
        // Text whitespace, whitespace text
        {"a ", {"a", ""}},
        {" a", {"", "a"}},
        {" aBc", {"", "aBc"}},
        {"\tx", {"", "x"}},
        // Text whitespace text
        {"a\tb", {"a", "b"}},
        {"a\t \t \t \tbbb", {"a", "bbb"}},
        {"a\t \t \t \t\nbb", {"a", "\nbb"}},
        // More starting/ending with whitespace
        {"\t\t\n a bB\t", {"", "\n", "a", "bB", ""}},
        {"\t\t\n!! xy      ", {"", "\n!!", "xy", ""}},
    };
    for (auto const &c : cases) {
        REQUIRE(splitWhitespace(c.first) == c.second);
    }
}