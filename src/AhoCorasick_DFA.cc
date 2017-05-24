#include "AhoCorasick.h"
#include <streambuf>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  std::string patterns_file_path(argv[1]);

  std::vector< std::string > patterns;

  std::ifstream patterns_file_content(patterns_file_path);
  std::string line;
  while(getline(patterns_file_content, line)) {
    patterns.push_back(line);
  }

  AhoCorasick matcher(patterns);

  matcher.print_dot_automata();
}
