#include "test/catch.hpp"
#include "DirectInstr.hpp"
#include "ImmediateInstr.hpp"
#include "SymbolInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include <tuple>
#include <iostream>

TEST_CASE("Test parseSymbolInstr") {
    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>> directs = {
        {"LDD", {"$na_me"}, Symbol(Name("na_me"), std::nullopt)},
        {"STD", {"EC"}, Symbol(std::nullopt, Number(0xEC))},
    };
    for (size_t i = 0; i < directs.size(); i++) {
        REQUIRE(
            dynamic_cast<DirectInstr&>(
                *parseSymbolInstr(std::get<0>(directs[i]), std::get<1>(directs[i]))
            ) == DirectInstr(std::get<0>(directs[i]), std::get<2>(directs[i]))
        );
    }

    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>> imms = {
        {"XORI", {"$TheName"}, Symbol(Name("TheName"), std::nullopt)},
        {"LDI",  {"A1"}, Symbol(std::nullopt, Number(0xA1))},
    };
    for (size_t i = 0; i < imms.size(); i++) {
        REQUIRE(
            dynamic_cast<ImmediateInstr&>(
                *parseSymbolInstr(std::get<0>(imms[i]), std::get<1>(imms[i]))
            ) == ImmediateInstr(std::get<0>(imms[i]), std::get<2>(imms[i]))
        );
    }

    std::vector<std::tuple<std::string, std::vector<std::string>>> bad = {
        // Unknown opcode
        {"",    {"$TheName"}},
        {"XOR", {"A"}},
        // Wrong # operands
        {"SUBI", {}},
        {"IN", {"1", "2"}},
        // Bad name
        {"ORI", {"$$name"}},
        // Bad number
        {"TSTI", {"HIJK"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(
            parseSymbolInstr(std::get<0>(bad[i]), std::get<1>(bad[i])), 
            ParseExn
        );
    }
}