#pragma once
#include "Matcher.h"
#include <set>
#include <vector>
#include <iostream>

class Trie  : public Matcher {
private:
  class Node {
  public:
    std::vector< Trie::Node* > adj;
    // even if the representative string is unique for each node, it can happen
    // that the trie class is constructed with a list of patterns that contains
    // repeated strings
    std::set< int > output;
    Node() {

    }
  };
  std::vector< std::string > _patterns;
  Trie::Node* _insert_word(Trie::Node* root, std::string w, int index, int output_index);
  Trie::Node* _root;
  void _erase_tree(Trie::Node* root);
public:
  const static int ALPHABET_SIZE = 1<<(8*sizeof(char));
  Trie(std::vector< std::string >& patterns);
  ~Trie();
  std::vector< std::vector< int > > find_matches(std::string& text);
};
