#include <string>
#include <vector>

#include "exceptions/ParseExn.hpp"
#include "test/catch.hpp"
#include "Name.hpp"

TEST_CASE("Test Name construction") {
    std::vector<std::string> good = {
        // One character
        "_", 
        "a",
        "B"
        // Multi-character
        "__",
        "AB",
        "b1",
        "aBcDe12345",
        "z_y_x_w_3_V_U" // All character types
    };

    for (size_t i = 0; i < good.size(); i++) {
        Name name(good[i]);
        REQUIRE(name.getName() == good[i]);
    }

    std::vector<std::string> bad = {
        // Empty
        "",
        // One character
        "!",
        " ",
        "\0",
        "1", // A number
        // Multi-character
        "a!",
        "badVari@ble",
        "1a", // Starts with number
        // Leading or trailing space
        "   abc",
        "var \t",
    };

    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(Name(bad[i]), ParseExn);
    }
}