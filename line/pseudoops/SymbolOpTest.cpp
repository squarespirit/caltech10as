#include "test/catch.hpp"
#include <memory>
#include <tuple>
#include "ByteOp.hpp"
#include "DataOp.hpp"
#include "OrgOp.hpp"
#include "SymbolOp.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test parseSymbolOp") {
    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>>
    byteops = {
        {".byte",   {"0"},      Symbol(Number(0))},
        {".byte",   {"$green"}, Symbol(Name("green"))},
    };
    for (size_t i = 0; i < byteops.size(); i++) {
        REQUIRE(
            dynamic_cast<ByteOp&>(
                *parseSymbolOp(std::get<0>(byteops[i]), std::get<1>(byteops[i]))
            ) == ByteOp(std::get<2>(byteops[i]))
        );
    }

    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>>
    dataops = {
        {".data",    {"123"},    Symbol(Number(0x123))},
        {".data",    {"$red"},   Symbol(Name("red"))},
    };
    for (size_t i = 0; i < dataops.size(); i++) {
        REQUIRE(
            dynamic_cast<DataOp&>(
                *parseSymbolOp(std::get<0>(dataops[i]), std::get<1>(dataops[i]))
            ) == DataOp(std::get<2>(dataops[i]))
        );
    }

    std::vector<std::tuple<std::string, std::vector<std::string>, Symbol>> orgops = {
        {".org",    {"123"},    Symbol(Number(0x123))},
        {".org",    {"$blue"},  Symbol(Name("blue"))}
    };
    for (size_t i = 0; i < orgops.size(); i++) {
        REQUIRE(
            dynamic_cast<OrgOp&>(
                *parseSymbolOp(std::get<0>(orgops[i]), std::get<1>(orgops[i])))
            == OrgOp(std::get<2>(orgops[i]))
        );
    }

    std::vector<std::pair<std::string, std::vector<std::string>>> bad = {
        {"data",    {"123"}}, // Bad opcode
        {".include", {"hello"}},
        {".data",   {}}, // Wrong # operands
        {".org",    {"a", "b"}},
        {".data",   {"", "", ""}},
        {".org",    {"FFGF"}}, // Bad symbol
        {".data",   {"$r#d"}},
    };
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(parseSymbolOp(bad[i].first, bad[i].second), ParseExn);
    }
}
