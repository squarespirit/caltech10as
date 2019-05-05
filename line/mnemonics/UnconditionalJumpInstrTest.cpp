#include "UnconditionalJumpInstr.hpp"
#include "exceptions/RangeExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test UnconditionalJumpInstr encode") {
    Context c;
    c.addLabel(Name("lab1"), Number(0x1234));
    c.addLabel(Name("lab2"), Number(0x1));
    c.addLabel(Name("maxLabel"), Number(PROGRAM_ADDRESS_SIZE - 1));
    c.addLabel(Name("big"), Number(PROGRAM_ADDRESS_SIZE));

    std::vector<std::pair<UnconditionalJumpInstr, uint16_t>> good = {
        {{"CALL", Name("lab1")}, 0xF234},
        {{"JMP", Name("lab2")}, 0xC001},
        {{"CALL", Name("maxLabel")}, 0xFFFF}};

    for (size_t i = 0; i < good.size(); i++) {
        REQUIRE(good[i].first.encode(c) == good[i].second);
    }

    // Label too big
    REQUIRE_THROWS_AS(UnconditionalJumpInstr("JMP", Name("big")).encode(c),
                      RangeExn);
}
