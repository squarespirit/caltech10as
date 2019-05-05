#include "test/catch.hpp"

#include "OrgOp.hpp"
#include "context/Context.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"
#include <tuple>

TEST_CASE("Test OrgOp apply") {
    Context c;
    c.setCurProgramAddress(0x5);
    c.addConstant(Name("const1"), Number(0x10));

    // Good symbol
    // Good number
    OrgOp(Symbol(Number(0x15))).apply(c);
    REQUIRE(c.getCurProgramAddress() == 0x15);
    // Good name
    OrgOp(Symbol(Name("const1"))).apply(c);
    REQUIRE(c.getCurProgramAddress() == 0x10);

    // Bad name
    REQUIRE_THROWS_AS(OrgOp(Symbol(Name("const2"))).apply(c), NameExn);
    // Number too large
    REQUIRE_THROWS_AS(OrgOp(Symbol(Number(0x2FFF))).apply(c), RangeExn);
}