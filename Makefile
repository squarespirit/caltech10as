CXX=g++
CXXFLAGS=-g -I. -Wall -Werror -std=c++17
LDFLAGS=-g
EXECS=TestMain

CONTEXT_OBJS = context/Context.o
CONTEXT_TEST_OBJS = context/ContextTest.o
DATATYPES_OBJS = $(addprefix datatypes/, \
	IncDecRegister.o Name.o Number.o NumberTypes.o Symbol.o Register.o \
	Whitespace.o)
DATATYPES_TEST_OBJS = $(addprefix datatypes/, \
	IncDecRegisterTest.o NameTest.o NumberTest.o SymbolTest.o WhitespaceTest.o)
EXCEPTION_OBJS = $(addprefix exceptions/, \
	AssemblyExn.o IncludeLoopExn.o NameExn.o ParseExn.o RangeExn.o)
LINE_OBJS = $(addprefix line/, LabelDef.o Line.o Operation.o)
LINE_TEST_OBJS = $(addprefix line/, LabelDefTest.o LineTest.o OperationTest.o)
LINE_MNEMONICS_OBJS = $(addprefix line/mnemonics/, \
	ALUDataInstr.o ConditionalJumpInstr.o DirectInstr.o Mnemonic.o \
	ImmediateInstr.o IndexedLoadStoreInstr.o LabelInstr.o NoOperandInstr.o \
	SymbolInstr.o UnconditionalJumpInstr.o)
LINE_MNEMONICS_TEST_OBJS = $(addprefix line/mnemonics/, \
	ALUDataInstrTest.o ConditionalJumpInstrTest.o DirectInstrTest.o \
	ImmediateInstrTest.o IndexedLoadStoreInstrTest.o LabelInstrTest.o \
	MnemonicTest.o NoOperandInstrTest.o SymbolInstrTest.o \
	UnconditionalJumpInstrTest.o)
LINE_PSEUDOOPS_OBJS = $(addprefix line/pseudoops/, \
	ByteOp.o ConstOp.o DataOp.o OrgOp.o IncludeOp.o PseudoOp.o SymbolOp.o)
LINE_PSEUDOOPS_TEST_OBJS = $(addprefix line/pseudoops/, \
	ByteOpTest.o ConstOpTest.o DataOpTest.o IncludeOpTest.o \
	OrgOpTest.o PseudoOpTest.o SymbolOpTest.o)
TEST_MAIN_OBJS = test/TestMain.o

ALL_BUILD_OBJS = $(CONTEXT_OBJS) $(DATATYPES_OBJS) $(EXCEPTION_OBJS) \
	$(LINE_OBJS) $(LINE_MNEMONICS_OBJS) $(LINE_PSEUDOOPS_OBJS)
ALL_TEST_OBJS = $(CONTEXT_TEST_OBJS) $(DATATYPES_TEST_OBJS) $(LINE_TEST_OBJS) \
	$(LINE_MNEMONICS_TEST_OBJS) $(LINE_PSEUDOOPS_TEST_OBJS) $(TEST_MAIN_OBJS)

.PHONY: all clean clean-libs cloc fmt lint test

all: $(EXECS)

# Use implicit .cpp -> .o rule to compile all .o files

TestMain: $(ALL_BUILD_OBJS) $(ALL_TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: TestMain
	./TestMain

cloc:
	cloc --not-match-f=catch.hpp --exclude-dir=.vscode .

clean:
	# Delete object files
	find . -name "*.o" -type f -delete
	rm -f $(EXECS)

fmt:
	# Do not format catch.hpp
	clang-format -i \
		`find . -name "*.cpp" -o  -name "*.hpp" ! -path "*test/catch.hpp"`

lint:
	# Do not check test files
	cppcheck --enable=all -q -I. --error-exitcode=1 --suppress="*:test/*" \
		--suppress="*:*Test.cpp" .