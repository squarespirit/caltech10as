#include "test/catch.hpp"

#include "DataOp.hpp"
#include "context/Context.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"

TEST_CASE("Test DataOp apply") {
    Context c;
    c.setCurDataAddress((number_t)0x5);
    c.addConstant(Name("const1"), Number(0x10));
    c.addConstant(Name("big"), Number(0xFFFF));

    // Good symbol
    // Good number
    DataOp(Symbol(Number(0x15))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x15);
    // Good name
    DataOp(Symbol(Name("const1"))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x10);

    // Bad name
    REQUIRE_THROWS_AS(DataOp(Symbol(Name("const2"))).apply(c), NameExn);
    // Number too large
    REQUIRE_THROWS_AS(DataOp(Symbol(Number(0xABC))).apply(c), RangeExn);
    // Name maps to number that is too large
    REQUIRE_THROWS_AS(DataOp(Symbol(Name("big"))).apply(c), RangeExn);
}