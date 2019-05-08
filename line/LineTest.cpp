#include "Line.hpp"
#include "Operation.hpp"
#include "exceptions/ParseExn.hpp"
#include "mnemonics/ALUDataInstr.hpp"
#include "mnemonics/DirectInstr.hpp"
#include "mnemonics/IndexedLoadStoreInstr.hpp"
#include "mnemonics/NoOperandInstr.hpp"
#include "mnemonics/UnconditionalJumpInstr.hpp"
#include "pseudoops/ConstOp.hpp"
#include "pseudoops/DataOp.hpp"
#include "pseudoops/OrgOp.hpp"
#include "test/catch.hpp"
#include <iostream>

TEST_CASE("Test Line parse") {
    // Good examples
    // Empty
    Line l = Line::parse("");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    l = Line::parse("     ");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    l = Line::parse("\t\t\t\t\t\t\t\t\t \t");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    // Comment
    l = Line::parse("  ; This is a comment asfoishdafhasf");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    // 2 ;'s
    l = Line::parse("  ; This is a comment ; This is still a comment");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    // Operation inside comment
    l = Line::parse(";ADD FF ");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    // Label inside comment
    // This is pathological if we parse for the ':' *first*.
    l = Line::parse("  ;  hello:");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    l = Line::parse("  ;  __label: .byte 0E");
    REQUIRE(!l.hasLabel());
    REQUIRE(!l.hasOperation());

    // Label only
    l = Line::parse("mylab:");
    REQUIRE(l.getLabel() == LabelDef(Name("mylab")));
    REQUIRE(!l.hasOperation());

    l = Line::parse("_:   ; // This is my label");
    REQUIRE(l.getLabel() == LabelDef(Name("_")));
    REQUIRE(!l.hasOperation());

    l = Line::parse("  def:;"); // Comment immediately after label
    REQUIRE(l.getLabel() == LabelDef(Name("def")));
    REQUIRE(!l.hasOperation());

    l = Line::parse(" abC:  ;::a::b::"); // A label behind a comment?
    REQUIRE(l.getLabel() == LabelDef(Name("abC")));
    REQUIRE(!l.hasOperation());

    // Pseudo-ops
    l = Line::parse("   .org 345   ; Set program address ");
    REQUIRE(!l.hasLabel());
    REQUIRE(dynamic_cast<OrgOp const &>(l.getOperation()) ==
            OrgOp(Symbol(Number(0x345))));

    l = Line::parse(".const  Constant \t ff00 ; The .const is ee11");
    REQUIRE(!l.hasLabel());
    REQUIRE(dynamic_cast<ConstOp const &>(l.getOperation()) ==
            ConstOp(Name("Constant"), Number(0xFF00)));

    // Pseudo-op and label
    l = Line::parse("addrEss:.data $dat ");
    REQUIRE(l.getLabel() == LabelDef(Name("addrEss")));
    REQUIRE(dynamic_cast<DataOp const &>(l.getOperation()) ==
            DataOp(Symbol(Name("dat"))));

    // Mnemonics
    // No space before comment
    l = Line::parse("    TAX;stores x in accumulator ");
    REQUIRE(!l.hasLabel());
    REQUIRE(dynamic_cast<NoOperandInstr const &>(l.getOperation()) ==
            NoOperandInstr("TAX"));

    l = Line::parse("ST\tX,0a;;;;;");
    REQUIRE(!l.hasLabel());
    REQUIRE(dynamic_cast<IndexedLoadStoreInstr const &>(l.getOperation()) ==
            IndexedLoadStoreInstr("ST", IncDecRegister(Register::X),
                                  Symbol(Number(0x0A))));

    // Mnemonic and label
    l = Line::parse("jumphere:CALL  \t\taddress      ; Target address");
    REQUIRE(l.getLabel() == LabelDef(Name("jumphere")));
    REQUIRE(dynamic_cast<UnconditionalJumpInstr const &>(l.getOperation()) ==
            UnconditionalJumpInstr("CALL", Name("address")));

    std::vector<std::string> bad = {
        // Bad "empty" examples
        "\n",
        "   $  ", // Random punctuation
        // Bad label
        ":", "              :\t", "extraspace :\t",
        // Multi label
        "one:   two:", "one:   tw2:  ADD 1",
        // Multi operation
        "INS\tDES", "ST S+,LDD 03",
    };
    for (std::string const &s : bad) {
        REQUIRE_THROWS_AS(Line::parse(s), ParseExn);
    }
}