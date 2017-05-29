#include "AhoCorasick.h"
#include "BruteForce.h"
#include "Trie.h"
#include "KMP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector< std::vector< int > > aho(std::vector < std::string > patterns, std::string text) {
 AhoCorasick matcher(patterns);
 return matcher.find_matches(text);
}

std::vector< std::vector< int > > trie(std::vector < std::string > patterns, std::string text) {
 Trie matcher(patterns);
 return matcher.find_matches(text);
}

std::vector< std::vector< int > > kmp(std::vector < std::string > patterns, std::string text) {
  std::vector< std::vector< int > > ret;
  for(int i=0; i<int(patterns.size()); ++i) {
    ret.push_back(KMP::find_matches(patterns[i], text));
  }
  return ret;
}

std::vector< std::vector< int > > bf(std::vector < std::string > patterns, std::string text) {
  std::vector< std::vector< int > > ret;
  for(int i=0; i<int(patterns.size()); ++i) {
    ret.push_back(BruteForce::find_matches(patterns[i], text));
  }
  return ret;
}

void print_beautified(std::vector< std::string > patterns, std::vector< std::vector< int > > results) {
  std::vector< std::pair< int, std::string > > freqs;
  for(int i=0; i<int(patterns.size()); ++i) {
    std::cout << patterns[i] << ": {";
    for(int j=0; j<int(results[i].size()); ++j) {
      if(j>0) std::cout << ", ";
      std::cout << results[i][j];
    }
    std::cout << "}" << std::endl;
  }
}

int main(int argc, char** argv) {
  std::string pattern_file(argv[1]);
  std::string text_file(argv[2]);
  std::string algorithm(argv[3]);
  std::ifstream pattern_handler(pattern_file);
  std::ifstream text_handler(text_file);
  std::vector< std::string > patterns;
  std::string _line;
  while(std::getline(pattern_handler, _line)) {
    patterns.push_back(_line);
  }
  std::ostringstream oss;
  oss << text_handler.rdbuf();
  std::string text = oss.str();
  std::vector< std::vector< int > > matches;
  if(algorithm == "aho") matches = aho(patterns, text);
  else if(algorithm == "kmp") matches = kmp(patterns, text);
  else if(algorithm == "trie") matches = trie(patterns, text);
  else matches = bf(patterns, text);
  print_beautified(patterns, matches);
}
