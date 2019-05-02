CXX=g++
CXXFLAGS=-g -I. -Wall -Werror -std=c++17
LDFLAGS=-g
EXECS=TestMain

CONTEXT_OBJS = context/Context.o
CONTEXT_TEST_OBJS = context/ContextTest.o
DATATYPES_OBJS = datatypes/Name.o datatypes/Number.o datatypes/Symbol.o datatypes/Register.o datatypes/IncDecSpec.o
DATATYPES_TEST_OBJS = datatypes/NameTest.o datatypes/NumberTest.o datatypes/SymbolTest.o
EXCEPTION_OBJS = exceptions/NameExn.o exceptions/ParseExn.o
LINE_OBJS = line/LabelDef.o
LINE_TEST_OBJS = line/LabelDefTest.o
TEST_OBJS = test/TestMain.o

ALL_BUILD_OBJS = $(CONTEXT_OBJS) $(DATATYPES_OBJS) $(EXCEPTION_OBJS) $(LINE_OBJS)
ALL_TEST_OBJS = $(CONTEXT_TEST_OBJS) $(DATATYPES_TEST_OBJS) $(LINE_TEST_OBJS) $(TEST_OBJS)

.PHONY: all test clean

all: $(EXECS)

datatypes/%.o: datatypes/%.cpp

exceptions/%.o: exceptions/%.cpp

test/%.o: test/%.cpp

TestMain: $(ALL_BUILD_OBJS) $(ALL_TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: TestMain
	./TestMain

clean:
	rm -f */*.o $(EXECS)
