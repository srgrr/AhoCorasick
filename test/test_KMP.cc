#include "gtest/gtest.h"
#include "KMP.h"
#include "BruteForce.h"
#include <iostream>
#include <vector>
#include <cstdlib>

namespace {

class KMPTest : public ::testing::Test {
 protected:

  KMPTest() {

  }

  virtual ~KMPTest() {

  }

  virtual void SetUp() {

  }

  virtual void TearDown() {

  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(KMPTest, prefix_test_1) {
  std::vector< int > got = KMP::get_prefix_table("evanev");
  //                            e  v  a  n  e  v  #
  std::vector< int > should = {-1, 0, 0, 0, 0, 1, 2};
  ASSERT_EQ(should, got);
}

TEST_F(KMPTest, prefix_test_2) {
  std::vector< int > got = KMP::get_prefix_table("abbabba");
  //                            a  b  b  a  b  b  a  #
  std::vector< int > should = {-1, 0, 0, 0, 1, 2, 3, 4};
  ASSERT_EQ(should, got);
}

TEST_F(KMPTest, match_test_1) {
  std::string pattern = "aba";
  std::string text = "ababa";
  std::vector< int > got = KMP::find_matches(pattern, text);
  std::vector< int > should = {0, 2};
  ASSERT_EQ(should, got);
}

TEST_F(KMPTest, match_test_2) {
  KMP matcher("aba");
  std::vector< int > got = matcher.find_matches("ababa");
  std::vector< int > should = {0, 2};
  ASSERT_EQ(should, got);
}

TEST_F(KMPTest, match_test_random) {
 std::srand(0);
 char pool[4] = {'A', 'C', 'T', 'G'};
 for(int i=0; i<100000; ++i) {
   int p = std::rand()%4 + 2;
   int t = std::rand()%1000 + 8;
   std::string pattern;
   std::string text;
   for(int j=0; j<p; ++j) pattern += pool[std::rand()%4];
   for(int j=0; j<t; ++j) text += pool[std::rand()%4];
   std::vector< int > bf = BruteForce::find_matches(pattern, text);
   std::vector< int > kmp = KMP::find_matches(pattern, text);
   ASSERT_EQ(bf, kmp);
 }
}

} // namespace
