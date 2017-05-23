#include "KMP.h"

KMP::KMP(std::string pattern) {
  _pattern = pattern;
  _prefix_table = KMP::get_prefix_table(pattern);
}

//static
std::vector< int > KMP::get_prefix_table(std::string pattern) {
  int n = int(pattern.size());
  std::vector< int > ret(n+1);
  ret[0] = -1;
  int l = -1, r = 0;
  while(r<n) {
    while(l>=0 && pattern[l] != pattern[r]) l = ret[l];
    ++l, ++r;
    ret[r] = l;
  }
  return ret;
}

//static
std::vector< int > KMP::get_matches(std::vector<int>& prefix_table,
                                           std::string pattern,
                                           std::string text) {
  std::vector< int > ret;
  int n = int(text.size());
  int l = 0, r = 0;
  while(r<n) {
    while(l>=0 && text[r] != pattern[l]) l = prefix_table[l];
    ++l, ++r;
    if(l == int(pattern.size())) {
      l = prefix_table[l];
      ret.push_back(r - int(pattern.size()));
    }
  }
  return ret;
}

//static
std::vector< int > KMP::get_matches(std::string pattern, std::string text) {
  std::vector< int > prefix_table = KMP::get_prefix_table(pattern);
  return KMP::get_matches(prefix_table, pattern, text);
}

std::vector< int > KMP::get_matches(std::string text) {
  return KMP::get_matches(_prefix_table, _pattern, text);
}
