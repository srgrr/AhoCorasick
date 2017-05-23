#pragma once
#include <iostream>
#include <vector>
#include <map>
/*
  An implementation of the Aho Corasick Algorithm.
*/

class AhoCorasick {
private:
  // Attributes
  std::vector< std::string > _patterns;

  // Methods
  void _build_automata();
public:
  AhoCorasick();
  AhoCorasick(std::vector< std::string > patterns);
  std::vector< std::vector<int> > find_matches(std::string text);
  std::map< std::string, std::vector< int > > find_matches_map(std::string text);
  // Getters and setters
  void set_patterns(std::vector< std::string > patterns);
  const std::vector< std::string >& get_patterns();
};
