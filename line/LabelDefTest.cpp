#include "test/catch.hpp"

#include "LabelDef.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/ParseExn.hpp"

TEST_CASE("Test LabelDef parsing") {
    std::vector<std::pair<std::string, std::string>> good = {
        {"a:", "a"}, {"_myLabel_:", "_myLabel_"}, {"lab123:", "lab123"}};
    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(LabelDef::parse(good[i].first) ==
                LabelDef(Name(good[i].second)));
    }

    std::vector<std::string> bad = {"",   // Empty label def
                                    ":",  // Empty label name
                                    " :", // Invalid name
                                    "$n@me:", "1hello:"};
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(LabelDef::parse(bad[i]), ParseExn);
    }
}

TEST_CASE("Test LabelDef apply") {
    // Successfully apply a label.
    Context c;
    c.addLabel(Name("lab1"), Number(1234));
    c.setCurProgramAddress(11);
    LabelDef(Name("lab2")).apply(c);
    REQUIRE(c.lookupLabel(Name("lab1")) == Number(1234));
    REQUIRE(c.lookupLabel(Name("lab2")) == Number(11));

    // Apply a label that already exists.
    REQUIRE_THROWS_AS(LabelDef(Name("lab1")).apply(c), NameExn);
}
