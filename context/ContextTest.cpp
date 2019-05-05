#include "test/catch.hpp"

#include "Context.hpp"
#include "datatypes/NumberTypes.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/RangeExn.hpp"

TEST_CASE("Test that Context persists labels") {
    Context c;
    c.addLabel(Name("lab1"), Number(1234));
    REQUIRE(c.lookupLabel(Name("lab1")) == Number(1234));
}

TEST_CASE("Test that adding duplicate labels to Context throws NameExn") {
    Context c;
    c.addLabel(Name("lab1"), Number(1234));
    c.addLabel(Name("lab2"), Number(2345));
    REQUIRE_THROWS_AS(c.addLabel(Name("lab1"), Number(3456)), NameExn);
}

TEST_CASE("Test that looking up undefined label in Context throws NameExn") {
    Context c;
    c.addLabel(Name("lab1"), Number(1234));
    c.addLabel(Name("lab2"), Number(2345));
    REQUIRE_THROWS_AS(c.lookupLabel(Name("lab3")), NameExn);
}

TEST_CASE("Test setting program address") {
    Context c;
    c.setCurProgramAddress(0x1111);
    REQUIRE(c.getCurProgramAddress() == 0x1111);
    c.setCurProgramAddress(PROGRAM_ADDRESS_SIZE - 1);
    REQUIRE(c.getCurProgramAddress() == PROGRAM_ADDRESS_SIZE - 1);
    REQUIRE_THROWS_AS(c.setCurProgramAddress(PROGRAM_ADDRESS_SIZE), RangeExn);
}

TEST_CASE("Test setting data address") {
    Context c;
    c.setCurDataAddress(DATA_ADDRESS_SIZE - 1);
    REQUIRE(c.getCurDataAddress() == DATA_ADDRESS_SIZE - 1);
    REQUIRE_THROWS_AS(c.setCurDataAddress(DATA_ADDRESS_SIZE), RangeExn);
}