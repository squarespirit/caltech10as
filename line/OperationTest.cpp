#include "Operation.hpp"
#include "exceptions/ParseExn.hpp"
#include "mnemonics/ALUDataInstr.hpp"
#include "mnemonics/DirectInstr.hpp"
#include "mnemonics/NoOperandInstr.hpp"
#include "pseudoops/ConstOp.hpp"
#include "pseudoops/OrgOp.hpp"
#include "test/catch.hpp"

TEST_CASE("Test Operation parse") {
    // Good examples
    // Pseudo-op
    std::unique_ptr<Operation> i = Operation::parse(".org  890");
    REQUIRE(dynamic_cast<OrgOp &>(*i) == OrgOp(Symbol(Number(0x890))));

    i = Operation::parse(".const  Constant \t ff00");
    REQUIRE(dynamic_cast<ConstOp &>(*i) ==
            ConstOp(Name("Constant"), Number(0xFF00)));

    // Mnemonic
    i = Operation::parse("SUB\tS,1");
    REQUIRE(dynamic_cast<ALUDataInstr &>(*i) ==
            ALUDataInstr("SUB", Register::S, Symbol(Number(1))));

    i = Operation::parse("NOP");
    REQUIRE(dynamic_cast<NoOperandInstr &>(*i) == NoOperandInstr("NOP"));

    i = Operation::parse("IN\t\t    $A");
    REQUIRE(dynamic_cast<DirectInstr &>(*i) ==
            DirectInstr("IN", Symbol(Name("A"))));

    // Bad opcode
    std::vector<std::string> bad = {
        "", ".none a", "INZ",
        " ADD 3",  // Leading space
        ".org AA " // Trailing space
    };
    for (std::string const &s : bad) {
        REQUIRE_THROWS_AS(Operation::parse(s), ParseExn);
    }
}