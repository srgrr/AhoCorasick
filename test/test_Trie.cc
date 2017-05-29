#include "gtest/gtest.h"
#include "BruteForce.h"
#include "Trie.h"

namespace {

class TrieTest : public ::testing::Test {
 protected:

  TrieTest() {

  }

  virtual ~TrieTest() {

  }

  virtual void SetUp() {

  }

  virtual void TearDown() {

  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(TrieTest, test_1) {
  std::vector< std::string > patterns = {
    "a"
  };
  Trie machine(patterns);
  std::vector< std::vector< int > > got = machine.find_matches("a");
  std::vector< std::vector< int > > should = {{0}};
  ASSERT_EQ(got, should);
}


TEST_F(TrieTest, test_2) {
  std::vector< std::string > patterns = {
    "aba"
  };
  Trie machine(patterns);
  std::vector< std::vector< int > > got = machine.find_matches("ababa");
  std::vector< std::vector< int > > should = {{0, 2}};
  ASSERT_EQ(got, should);
}


TEST_F(TrieTest, test_3) {
  std::vector< std::string > patterns = {
    "ab",
    "ba",
    "aba"
  };
  Trie machine(patterns);
  std::vector< std::vector< int > > got = machine.find_matches("aba");
  std::vector< std::vector< int > > should = {{0}, {1}, {0}};
  ASSERT_EQ(got, should);
}

// This test checks also that no big memory leaks are present
TEST_F(TrieTest, test_random) {
  std::srand(1);
  char pool[4] = {'A', 'C', 'T', 'G'};
  for(int tc=0; tc<10000; ++tc) {
    int num_patterns = std::rand()%10 + 2;
    std::vector < std::string > patterns(num_patterns);
    for(int j=0; j<num_patterns; ++j) {
      int str_len = std::rand()%5 + 2;
      for(int k=0; k<str_len; ++k) patterns[j] += pool[std::rand()%4];
    }

    std::string text;
    int text_len = std::rand()%1000 + 12;
    for(int i=0; i<text_len; ++i) {
      text += pool[std::rand()%4];
    }

    std::vector< std::vector< int > > bruteforce_ans(num_patterns);
    for(int i=0; i<num_patterns; ++i) {
      bruteforce_ans[i] = BruteForce::find_matches(patterns[i], text);
    }

    Trie matcher(patterns);
    std::vector< std::vector< int > > Trie_ans = matcher.find_matches(text);
    ASSERT_EQ(bruteforce_ans, Trie_ans);
  }
}

}
