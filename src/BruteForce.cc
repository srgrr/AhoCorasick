#include "BruteForce.h"

std::vector< int > BruteForce::_find_matches(std::string& pattern, std::string text) {
  std::vector< int > ret;
  int n = int(text.size());
  int m = int(pattern.size());
  for(int i=0; i<n-m+1; ++i) {
    bool ok = true;
    for(int j=0; j<m && ok; ++j) ok = text[i+j] == pattern[j];
    if(ok) ret.push_back(i);
  }
  return ret;
}

std::vector< std::vector< int > > BruteForce::find_matches(std::string& text) {
  std::vector< std::vector< int > > ret(_patterns.size());
  for(int i=0; i<int(_patterns.size()); ++i) {
    ret[i] = _find_matches(_patterns[i], text);
  }
  return ret;
}
