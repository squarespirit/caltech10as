CXX=clang++
CXXFLAGS=-g -I. -std=c++14
LDFLAGS=-g
EXECS=TestMain

.PHONY: all test clean

all: $(EXECS)

datatypes/%.o: datatypes/%.cpp

exceptions/%.o: exceptions/%.cpp

test/%.o: test/%.cpp

TestMain: test/TestMain.o datatypes/NameTest.o datatypes/Name.o exceptions/ParseExn.o
	$(CXX) $(LDFLAGS) -o $@ $^

test: TestMain
	./TestMain

clean:
	rm -f */*.o $(EXECS)
