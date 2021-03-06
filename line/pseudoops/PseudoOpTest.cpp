#include "ByteOp.hpp"
#include "ConstOp.hpp"
#include "DataOp.hpp"
#include "IncludeOp.hpp"
#include "OrgOp.hpp"
#include "PseudoOp.hpp"
#include "datatypes/Symbol.hpp"
#include "exceptions/ParseExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test PseudoOp parse") {
    // Good examples - 1 of each op
    REQUIRE(dynamic_cast<ByteOp &>(*PseudoOp::parseOp(".byte", {"AB"})) ==
            ByteOp(Symbol(Number(0xAB))));
    REQUIRE(dynamic_cast<ConstOp &>(
                *PseudoOp::parseOp(".const", {"name", "123"})) ==
            ConstOp(Name("name"), Number(0x123)));
    REQUIRE(dynamic_cast<DataOp &>(*PseudoOp::parseOp(".data", {"$dat"})) ==
            DataOp(Symbol(Name("dat"))));
    REQUIRE(dynamic_cast<IncludeOp &>(*PseudoOp::parseOp(
                ".include", {"fileName.file"})) == IncludeOp("fileName.file"));
    REQUIRE(dynamic_cast<OrgOp &>(*PseudoOp::parseOp(".org", {"BCD"})) ==
            OrgOp(Symbol(Number(0xBCD))));

    // Bad examples
    // Unknown opcode
    REQUIRE_THROWS_AS(PseudoOp::parseOp("", {}), ParseExn);
    REQUIRE_THROWS_AS(PseudoOp::parseOp(".op", {"a", "b"}), ParseExn);
}