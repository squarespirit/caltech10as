#include "ConditionalJumpInstr.hpp"
#include "LabelInstr.hpp"
#include "UnconditionalJumpInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test parseLabelInstr") {
    std::vector<std::tuple<std::string, std::vector<std::string>,
                           UnconditionalJumpInstr>>
        uncond = {
            {"CALL", {"na_me"}, {"CALL", Name("na_me")}},
            {"JMP", {"_ABEL"}, {"JMP", Name("_ABEL")}},
        };
    for (auto const &t : uncond) {
        REQUIRE(dynamic_cast<UnconditionalJumpInstr &>(*parseLabelInstr(
                    std::get<0>(t), std::get<1>(t))) == std::get<2>(t));
    }

    std::vector<
        std::tuple<std::string, std::vector<std::string>, ConditionalJumpInstr>>
        cond = {
            {"JB", {"a"}, {"JB", Name("a")}},
            {"JC", {"_1"}, {"JC", Name("_1")}},
        };
    for (auto const &t : cond) {
        REQUIRE(dynamic_cast<ConditionalJumpInstr &>(*parseLabelInstr(
                    std::get<0>(t), std::get<1>(t))) == std::get<2>(t));
    }

    // Various parse errors
    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        // Unknown opcode
        {"", {"TheName"}},
        {"JJ", {"A"}},
        // Wrong # operands
        {"JMP", {}},
        {"JA", {"1", "2"}},
        // Bad label
        {"CALL", {"$name"}},
        {"JG", {"lab'l"}},
    };
    for (auto const &p : bad) {
        REQUIRE_THROWS_AS(parseLabelInstr(p.first, p.second), ParseExn);
    }
}