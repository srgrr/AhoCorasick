#include "KMP.h"

KMP::KMP(std::vector< std::string >& patterns) : Matcher(patterns) {
  for(std::string& pattern : _patterns) {
    _prefix_tables.push_back(_get_prefix_table(pattern));
  }
}

std::vector< int > KMP::_get_prefix_table(std::string& pattern) {
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

std::vector< int > KMP::_find_matches(std::vector<int>& prefix_table,
                                      std::string& pattern,
                                      std::string& text) {
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

std::vector< std::vector< int > > KMP::find_matches(std::string& text) {
  std::vector< std::vector< int > > ret(_patterns.size());
  for(int i=0; i<int(_patterns.size()); ++i) {
    ret[i] = _find_matches(_prefix_tables[i], _patterns[i], text);
  }
  return ret;
}
