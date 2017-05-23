#pragma once
#include <iostream>
#include <vector>

/*
  An implementation of the KMP algorithm.
  This algorithm is implemented for comparison purposes.
*/

class KMP {
private:
  std::string _pattern;
  std::vector< int > _prefix_table;
public:
  KMP(std::string pattern);
  static std::vector< int > get_prefix_table(std::string pattern);
  static std::vector< int > get_matches(std::vector<int>& prefix_table,
                                        std::string pattern,
                                        std::string text);
  static std::vector< int > get_matches(std::string pattern, std::string text);
  std::vector< int > get_matches(std::string text);
};
