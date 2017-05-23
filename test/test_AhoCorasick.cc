#include "gtest/gtest.h"
#include "AhoCorasick.h"
#include <iostream>
#include <vector>

namespace {

class AhoCorasickTest : public ::testing::Test {
 protected:

  AhoCorasickTest() {

  }

  virtual ~AhoCorasickTest() {

  }

  virtual void SetUp() {

  }

  virtual void TearDown() {

  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(AhoCorasickTest, test_1) {
  std::vector< std::string > patterns = {
    "ab",
    "ba",
    "aba"
  };
  AhoCorasick machine(patterns);
  std::vector< std::vector< int > > got = machine.find_matches("aba");
  std::vector< std::vector< int > > should = {{0}, {1}, {0}};
  ASSERT_EQ(got, should);
}

} // namespace