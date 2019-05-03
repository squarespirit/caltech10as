#include "test/catch.hpp"

#include "DataOp.hpp"
#include "exceptions/RangeExn.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "context/Context.hpp"

TEST_CASE("Test DataOp apply") {
    Context c;
    c.setCurDataAddress((number_t) 0x5);
    c.addConstant(Name("const1"), Number(0x10));
    c.addConstant(Name("big"), Number(0xFFFF));
    
    // Good symbol
    // Good number
    DataOp(Symbol(std::nullopt, Number(0x15))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x15);
    // Good name
    DataOp(Symbol(Name("const1"), std::nullopt)).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x10);

    // Bad name
    REQUIRE_THROWS_AS(
        DataOp(Symbol(Name("const2"), std::nullopt)).apply(c),
        NameExn
    );
    // Number too large
    REQUIRE_THROWS_AS(
        DataOp(Symbol(std::nullopt, Number(0xABC))).apply(c),
        RangeExn
    );
    // Name maps to number that is too large
    REQUIRE_THROWS_AS(
        DataOp(Symbol(Name("big"), std::nullopt)).apply(c),
        RangeExn
    );
}