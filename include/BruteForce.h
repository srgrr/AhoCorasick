#pragma once
#include "Matcher.h"
#include <iostream>
#include <vector>

class BruteForce : public Matcher {
private:
  std::vector< int > _find_matches(std::string& pattern, std::string text);
public:
  BruteForce(std::vector< std::string >& patterns) : Matcher(patterns) {}
  std::vector< std::vector< int > > find_matches(std::string& text);
};
