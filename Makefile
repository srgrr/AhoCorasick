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
TEST_FLAGS=${RELEASE_FLAGS} ${GTEST_FLAGS}

# OBJECT GROUPS
_AHO_CORASICK_OBJECTS=AhoCorasick.o
AHO_CORASICK_OBJECTS=$(patsubst %,$(OBJECT)/%, $(_AHO_CORASICK_OBJECTS))
TEST_AHO_CORASICK_OBJECTS=$(patsubst %,$(OBJECT)/test_%,$(_AHO_CORASICK_OBJECTS))

_KMP_OBJECTS=KMP.o
KMP_OBJECTS=$(patsubst %,$(OBJECT)/%, $(_KMP_OBJECTS))
TEST_KMP_OBJECTS=$(patsubst %,$(OBJECT)/test_%,$(_KMP_OBJECTS))

_BRUTEFORCE_OBJECTS=BruteForce.o
BRUTEFORCE_OBJECTS=$(patsubst %,$(OBJECT)/%, $(_BRUTEFORCE_OBJECTS))
TEST_BRUTEFORCE_OBJECTS=$(patsubst %,$(OBJECT)/test_%,$(_BRUTEFORCE_OBJECTS))

_TEST_SOURCES=test_AhoCorasick.cc test_KMP.cc
TEST_SOURCES=$(patsubst %,$(TEST)/%,$(_TEST_SOURCES))



# RULES
${OBJECT}/test_%.o: ${SRC}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${TEST_FLAGS}

${OBJECT}/test_%.o: ${TEST}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${TEST_FLAGS}

${OBJECT}/%.o: ${SRC}/%.cc
	g++ -c -o $@ $< ${GCC_FLAGS} ${RELEASE_FLAGS}

test_kmp: ${TEST}/test_KMP.cc ${TEST_KMP_OBJECTS} ${BRUTEFORCE_OBJECTS}
	g++ -o ${TESTBIN}/test_KMP ${TEST}/test_KMP.cc ${TEST_KMP_OBJECTS} ${BRUTEFORCE_OBJECTS} ${TEST_FLAGS}

test_aho_corasick: ${TEST}/test_AhoCorasick.cc ${TEST_AHO_CORASICK_OBJECTS}
	g++ -o ${TESTBIN}/test_AhoCorasick ${TEST}/test_AhoCorasick.cc ${TEST_AHO_CORASICK_OBJECTS} ${TEST_FLAGS}

aho_corasick_automata: ${SRC}/AhoCorasick_DFA.cc ${AHO_CORASICK_OBJECTS}
	g++ -o ${BIN}/AhoCorasick_DFA ${SRC}/AhoCorasick_DFA.cc ${AHO_CORASICK_OBJECTS} ${RELEASE_FLAGS}

tests_allinone: ${TEST_SOURCES} ${TEST_AHO_CORASICK_OBJECTS} ${TEST_KMP_OBJECTS} ${BRUTEFORCE_OBJECTS}
	g++ -o ${TESTBIN}/main ${TEST}/test_Main.cc ${TEST_SOURCES} ${TEST_AHO_CORASICK_OBJECTS}  ${TEST_KMP_OBJECTS} ${BRUTEFORCE_OBJECTS} ${TEST_FLAGS} -lgtest_main

main: ${MAIN_OBJECTS} ${AHO_CORASICK_OBJECTS} ${BRUTEFORCE_OBJECTS} ${KMP_OBJECTS}
	g++ -o ${BIN}/main ${SRC}/main.cc ${AHO_CORASICK_OBJECTS} ${BRUTEFORCE_OBJECTS} ${KMP_OBJECTS} ${RELEASE_FLAGS}

all_tests: tests_allinone

all: main all_tests aho_corasick_automata

clean:
	rm -rf ${OBJECT}
	rm -rf ${BIN}
	rm -rf ${TESTBIN}
	mkdir ${OBJECT}
	mkdir ${BIN}
	mkdir ${TESTBIN}
