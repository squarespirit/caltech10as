#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Number.hpp"
#include "exceptions/ParseExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test Number construction") {
    std::vector<std::pair<std::string, number_t>> good = {
        {"0", 0},         {"1", 1},         {"a", 0xA},      {"A", 0xA},
        {"A01B", 0xA01B}, {"bCdE", 0xBCDE}, {"FFFF", 0xFFFF}};

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(Number(good[i].first).getNumber() == good[i].second);
    }

    std::vector<std::string> bad = {// Empty
                                    "",
                                    // Invalid character
                                    "g", "123G", " 12", "1\01",
                                    // Too long
                                    "00001", // Leading 0s are bad unfortunately
                                    "a1234", "qwerty"};

    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(Number(bad[i]), ParseExn);
    }
}