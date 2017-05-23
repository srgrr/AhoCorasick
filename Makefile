# FOLDERS
SRC=src
INCLUDE=include
TEST=test
BIN=bin
TESTBIN=testbin
OBJECT=obj

# COMPILER FLAGS
GTEST_FLAGS=-lgtest -lgtest_main -pthread
GCC_FLAGS=-std=c++0x -Wall -pedantic -I${INCLUDE}
DEBUG_FLAGS=-O0 -gstabs+
RELEASE_FLAGS=-O2 ${GCC_FLAGS}
TEST_FLAGS=${DEBUG_FLAGS} ${GTEST_FLAGS} ${GCC_FLAGS}

# OBJECT GROUPS
_AHO_CORASICK_OBJECTS=AhoCorasick.o
AHO_CORASICK_OBJECTS=$(patsubst %,$(OBJECT)/%, $(_AHO_CORASICK_OBJECTS))
TEST_AHO_CORASICK_OBJECTS=$(patsubst %,$(OBJECT)/test_%,$(_AHO_CORASICK_OBJECTS))

_TEST_SOURCES=test_AhoCorasick.cc
TEST_SOURCES=$(patsubst %,$(TEST)/%,$(_TEST_SOURCES))

# RULES
${OBJECT}/test_%.o: ${SRC}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${DEBUG_FLAGS}

${OBJECT}/test_%.o: ${TEST}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${DEBUG_FLAGS}

${OBJECT}/%.o: ${SRC}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${RELEASE_FLAGS}

test_aho_corasick: ${TEST}/test_AhoCorasick.cc ${TEST_AHO_CORASICK_OBJECTS}
	g++ -o ${TESTBIN}/test_AhoCorasick ${TEST}/test_AhoCorasick.cc ${TEST_AHO_CORASICK_OBJECTS} ${TEST_FLAGS}

tests_allinone: clean ${TEST_SOURCES} ${TEST_AHO_CORASICK_OBJECTS}
	g++ -o ${TESTBIN}/main ${TEST_SOURCES} ${TEST_AHO_CORASICK_OBJECTS} ${TEST_FLAGS}

main: clean ${MAIN_OBJECTS} ${AHO_CORASICK_OBJECTS}
	g++ -o ${BIN}/main ${SRC}/main.cc ${AHO_CORASICK_OBJECTS} ${RELEASE_FLAGS}

all_tests: tests_allinone

all: main

clean:
	rm -rf ${OBJECT}
	rm -rf ${BIN}
	rm -rf ${TESTBIN}
	mkdir ${OBJECT}
	mkdir ${BIN}
	mkdir ${TESTBIN}
