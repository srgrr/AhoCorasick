#pragma once
#include <iostream>
#include <vector>
#include <map>


class Node {
public:
  // "goto" function according to the original AhoCorasick paper
  // here a null pointer represents a situation where g(s, a) = fail
  std::vector< Node* > adj;
  // fail function
  Node* fail;
  // output function
  std::vector< int > output;
  Node() {
    fail = NULL;
  }
};

/*
  An implementation of the Aho Corasick Algorithm.
*/
class AhoCorasick {
private:
  // "Trie" related data and methods


  Node* _root;

  // this function is equivalent to the "enter" procedure described in
  // algorithm 1
  Node* _trie_insert(Node* root, std::string w, int index, int output_index);

  // Attributes
  std::vector< std::string > _patterns;

  // Methods
  void _build_automata();
public:
  const static int ALPHABET_SIZE = 1<<(8*sizeof(char));
  AhoCorasick();
  AhoCorasick(std::vector< std::string > patterns);
  std::vector< std::vector<int> > find_matches(std::string text);
  std::map< std::string, std::vector< int > > find_matches_map(std::string text);
  // Getters and setters
  void set_patterns(std::vector< std::string > patterns);
  const std::vector< std::string >& get_patterns();
};
