#include "ALUDataInstr.hpp"
#include "ConditionalJumpInstr.hpp"
#include "DirectInstr.hpp"
#include "ImmediateInstr.hpp"
#include "IndexedLoadStoreInstr.hpp"
#include "Mnemonic.hpp"
#include "NoOperandInstr.hpp"
#include "UnconditionalJumpInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test Mnemonic parse") {
    // Good examples - 1 of each instruction

    std::unique_ptr<Mnemonic> i = Mnemonic::parseOp("ADC", {"X,50"});
    REQUIRE(dynamic_cast<ALUDataInstr &>(*i) ==
            ALUDataInstr("ADC", Register::X, Symbol(Number(0x50))));

    i = Mnemonic::parseOp("ANDI", {"F"});
    REQUIRE(dynamic_cast<ImmediateInstr &>(*i) ==
            ImmediateInstr("ANDI", Symbol(Number(0x0F))));

    i = Mnemonic::parseOp("CLC", {});
    REQUIRE(dynamic_cast<NoOperandInstr &>(*i) == NoOperandInstr("CLC"));

    i = Mnemonic::parseOp("LDD", {"A1"});
    REQUIRE(dynamic_cast<DirectInstr &>(*i) ==
            DirectInstr("LDD", Symbol(Number(0xA1))));

    i = Mnemonic::parseOp("ST", {"-X,$off"});
    REQUIRE(dynamic_cast<IndexedLoadStoreInstr &>(*i) ==
            IndexedLoadStoreInstr("ST",
                                  IncDecRegister(Register::X, true, false),
                                  Symbol(Name("off"))));

    i = Mnemonic::parseOp("JNC", {"far"});
    REQUIRE(dynamic_cast<ConditionalJumpInstr &>(*i) ==
            ConditionalJumpInstr("JNC", Name("far")));

    i = Mnemonic::parseOp("CALL", {"funC"});
    REQUIRE(dynamic_cast<UnconditionalJumpInstr &>(*i) ==
            UnconditionalJumpInstr("CALL", Name("funC")));

    // Unknown opcode
    REQUIRE_THROWS_AS(
        Mnemonic::parseOp("XYZ", {"a", "b", "c", "D", "$e", "ff"}), ParseExn);
    REQUIRE_THROWS_AS(Mnemonic::parseOp(".a", {}), ParseExn);
}