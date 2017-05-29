#pragma once
#include <set>
#include <vector>
#include <iostream>

class TrieNode {
public:
  std::vector< TrieNode* > adj;
  // even if the representative string is unique for each node, it can happen
  // that the trie class is constructed with a list of patterns that contains
  // repeated strings
  std::set< int > output;
  TrieNode() {

  }
};

class Trie {
private:
  std::vector< std::string > _patterns;
  TrieNode* _insert_word(TrieNode* root, std::string w, int index, int output_index);
  TrieNode* _root;
public:
  const static int ALPHABET_SIZE = 1<<(8*sizeof(char));
  Trie(std::vector< std::string > patterns);
  ~Trie();
  std::vector< std::vector< int > > find_matches(std::string text);
};
