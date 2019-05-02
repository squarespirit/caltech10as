#include "test/catch.hpp"

#include "Context.hpp"
#include "exceptions/NameExn.hpp"


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