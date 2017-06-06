#pragma once
#include "Matcher.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

/*
  An implementation of the Aho Corasick Algorithm.
*/
class AhoCorasick : public Matcher {
private:
  // "Trie" related data and methods
  class Node {
  public:
    // "goto" function according to the original AhoCorasick paper
    // here a null pointer represents a situation where g(s, a) = fail
    std::vector< Node* > adj;
    // fail function
    Node* fail;
    // output function
    std::set< int > output;
    Node() {
      fail = NULL;
    }
    ~Node() {

    }
  };

  AhoCorasick::Node* _root;

  // this function is equivalent to the "enter" procedure described in
  // algorithm 1
  AhoCorasick::Node* _trie_insert(AhoCorasick::Node* root, std::string w, int index, int output_index);

  // Attributes
  std::map< Node*, std::string > _label_map;

  // Methods
  void _build_automata();
  void _erase_tree(AhoCorasick::Node* root);
  void _set_patterns(std::vector< std::string >& patterns);
  void _label_automata(AhoCorasick::Node* root, std::string pref);
public:
  const static int ALPHABET_SIZE = 1<<(8*sizeof(char));
  ~AhoCorasick();
  AhoCorasick(std::vector< std::string >& patterns);
  std::vector< std::vector<int> > find_matches(std::string& text);
  void print_dot_automata();
};
