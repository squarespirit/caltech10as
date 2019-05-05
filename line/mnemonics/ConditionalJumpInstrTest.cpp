#include "ConditionalJumpInstr.hpp"
#include "exceptions/RangeExn.hpp"
#include "test/catch.hpp"
#include <iostream>

TEST_CASE("Test ConditionalJumpInstr encode") {
    Context c;
    c.setCurProgramAddress(0x1000);
    c.addLabel(Name("backone"), Number(0x0FFF));
    c.addLabel(Name("here"), Number(0x1000));
    c.addLabel(Name("ahead"), Number(0x1001));
    c.addLabel(Name("behind"), Number(0x0FFE));
    c.addLabel(Name("max"), Number(0x1080));
    c.addLabel(Name("pastmax"), Number(0x1081));
    c.addLabel(Name("min"), Number(0x0F81));
    c.addLabel(Name("pastmin"), Number(0x0F80));
    c.addLabel(Name("first"), Number(0x0000));
    c.addLabel(Name("last"), Number(0x1FFF));

    std::vector<std::pair<ConditionalJumpInstr, uint16_t>> good = {
        {{"JA", Name("backone")}, 0x88FE}, {{"JAE", Name("here")}, 0x8CFF},
        {{"JL", Name("ahead")}, 0xB800},   {{"JLE", Name("behind")}, 0xACFD},
        {{"JU", Name("max")}, 0xBF7F},     {{"JV", Name("min")}, 0xAB80},
    };

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(good[i].first.encode(c) == good[i].second);
    }

    // All are out of range
    std::vector<ConditionalJumpInstr> bad = {{"JBE", Name("pastmax")},
                                             {"JG", Name("pastmin")},
                                             {"JNS", Name("first")},
                                             {"JS", Name("last")}};
    for (size_t i = 0; i < bad.size(); i++) {
        REQUIRE_THROWS_AS(bad[i].encode(c), RangeExn);
    }
}
