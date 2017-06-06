#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

class Matcher {
protected:
  std::vector< std::string > _patterns;
public:
  Matcher(std::vector< std::string >& patterns);
  virtual std::vector< std::vector< int > > find_matches(std::string& text) {
    std::cout << "Do NOT call me!" << std::endl;
    std::exit(1);
  }
};
