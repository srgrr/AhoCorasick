#pragma once
#include "Matcher.h"
#include <iostream>
#include <vector>

/*
  An implementation of the KMP algorithm.
  This algorithm is implemented for comparison purposes.
*/

class KMP : public Matcher {
private:
  std::vector< std::vector< int > > _prefix_tables;
  std::vector< int > _find_matches(std::vector< int >& prefix_table,
                                   std::string& pattern,
                                   std::string& text);
  std::vector< int > _get_prefix_table(std::string& pattern);
public:
  KMP(std::vector< std::string >& patterns);
  std::vector< std::vector< int > > find_matches(std::string& text);
};
