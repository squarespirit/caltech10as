#include "test/catch.hpp"
#include "ByteOp.hpp"
#include "datatypes/NumberTypes.hpp"
#include "exceptions/RangeExn.hpp"

TEST_CASE("Test ByteOp apply") {
    Context c;
    c.setCurDataAddress((number_t) 0x5);
    c.addConstant(Name("const1"), Number(0x10));
    c.addConstant(Name("big"), Number(0xFFFF));

    // Good data value
    // Good number
    ByteOp(Symbol(Number(0x15))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x6);
    // Good name
    ByteOp(Symbol(Name("const1"))).apply(c);
    REQUIRE(c.getCurDataAddress() == 0x7);

    // Data value too large
    // Large number
    REQUIRE_THROWS_AS(
        ByteOp(Symbol(Number(DATA_VALUE_SIZE))).apply(c),
        RangeExn
    );
    // Large name
    REQUIRE_THROWS_AS(
        ByteOp(Symbol(Name("big"))).apply(c),
        RangeExn
    );
}