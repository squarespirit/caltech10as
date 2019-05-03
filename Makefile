CXX=g++
CXXFLAGS=-g -I. -Wall -Werror -std=c++17
LDFLAGS=-g
EXECS=TestMain

CONTEXT_OBJS = context/Context.o
CONTEXT_TEST_OBJS = context/ContextTest.o
DATATYPES_OBJS = $(addprefix datatypes/, Name.o Number.o Symbol.o Register.o IncDecSpec.o)
DATATYPES_TEST_OBJS = $(addprefix datatypes/, NameTest.o NumberTest.o SymbolTest.o)
EXCEPTION_OBJS = $(addprefix exceptions/, RangeExn.o NameExn.o ParseExn.o)
LINE_OBJS = $(addprefix line/, LabelDef.o)
LINE_TEST_OBJS = $(addprefix line/, LabelDefTest.o)
LINE_PSEUDOOPS_OBJS = $(addprefix line/pseudoops/, DataOp.o OrgOp.o PseudoOp.o)
LINE_PSEUDOOPS_TEST_OBJS = $(addprefix line/pseudoops/, DataOpTest.o OrgOpTest.o)
TEST_MAIN_OBJS = test/TestMain.o

ALL_BUILD_OBJS = $(CONTEXT_OBJS) $(DATATYPES_OBJS) $(EXCEPTION_OBJS) $(LINE_OBJS) $(LINE_PSEUDOOPS_OBJS)
ALL_TEST_OBJS = $(CONTEXT_TEST_OBJS) $(DATATYPES_TEST_OBJS) $(LINE_TEST_OBJS) $(LINE_PSEUDOOPS_TEST_OBJS) $(TEST_MAIN_OBJS)

.PHONY: all test clean

all: $(EXECS)

datatypes/%.o: datatypes/%.cpp

exceptions/%.o: exceptions/%.cpp

line/%.o: line/%.cpp

line/pseudoops/%.o: line/pseudoops/%.cpp

test/%.o: test/%.cpp

TestMain: $(ALL_BUILD_OBJS) $(ALL_TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: TestMain
	./TestMain

clean:
	rm -f */*.o $(EXECS)
