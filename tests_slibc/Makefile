include ../VERSION
include ../Makefile.inc

.PHONY: all test clean

EXE=test_slibc

TEST_OBJS=TestString.o TestStdioFmt.o TestStdlib.o Launcher.o \
	 RuntimeConstraintViolation.o TestTemplateOverloads.o TestTime.o TestStdio.o

all: $(EXE)

$(EXE): $(TEST_OBJS) ../src/$(SLIBC_LIB_CPP)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(TEST_OBJS) -I../ -L../src/ -L${CPPUNIT_PATH}/lib -lstdc++ -lcppunit -ldl -lslibc

TestStdioFmt.o: TestStdioFmt.cpp
	$(CXX) $(CXXFLAGS) -Wno-format-extra-args  -Wno-format -Wno-uninitialized -I../ -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I../ -c -o $@ $<

test: $(EXE) ../src/$(SLIBC_LIB_CPP_SO)
	sh runtest.sh

clean: 
	rm -f *.o *.gcda *.gcno *.gcov $(EXE)
