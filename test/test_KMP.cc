#include "gtest/gtest.h"
#include "Matcher.h"
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


TEST_F(KMPTest, match_test_1) {
  std::string pattern = "aba";
  std::string text = "ababa";
  std::vector< std::string > patterns = {pattern};
  KMP* matcher = new KMP(patterns);
  std::vector< std::vector< int > > got = matcher->find_matches(text);
  std::vector< int > should = {0, 2};
  ASSERT_EQ(should, got[0]);
}

TEST_F(KMPTest, match_test_random) {
 std::srand(0);
 char pool[4] = {'A', 'C', 'T', 'G'};
 std::vector< std::string > patterns;
 std::vector< std::string > texts;
 for(int i=0; i<100; ++i) {
   int p = std::rand()%4 + 2;
   int t = std::rand()%100 + 8;
   std::string pattern;
   std::string text;
   for(int j=0; j<p; ++j) pattern += pool[std::rand()%4];
   for(int j=0; j<t; ++j) text += pool[std::rand()%4];
   patterns.push_back(pattern);
   texts.push_back(text);
 }
 KMP* matcher1 = new KMP(patterns);
 BruteForce* matcher2 = new BruteForce(patterns);
 for(std::string& text : texts) {
   auto res1 = matcher1->find_matches(text);
   auto res2 = matcher2->find_matches(text);
   ASSERT_EQ(res1, res2);
 }
}

} // namespace
