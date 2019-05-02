CXX=g++
CXXFLAGS=-g -I. -Wall -Werror -std=c++17
LDFLAGS=-g
EXECS=TestMain

CONTEXT_OBJS = context/Context.o
DATATYPES_OBJS = datatypes/Name.o datatypes/Number.o datatypes/Symbol.o
DATATYPES_TEST_OBJS = datatypes/NameTest.o datatypes/NumberTest.o datatypes/SymbolTest.o
EXCEPTION_OBJS = exceptions/NameExn.o exceptions/ParseExn.o
TEST_OBJS = test/TestMain.o

.PHONY: all test clean

all: $(EXECS)

datatypes/%.o: datatypes/%.cpp

exceptions/%.o: exceptions/%.cpp

test/%.o: test/%.cpp

TestMain: $(CONTEXT_OBJS) $(DATATYPES_OBJS) $(DATATYPES_TEST_OBJS) $(EXCEPTION_OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: TestMain
	./TestMain

clean:
	rm -f */*.o $(EXECS)
