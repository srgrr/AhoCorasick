#include "AhoCorasick.h"

/*
  This method builds the pattern matching machine that is used to find
  occurrences of the patterns on a given text.

  As explained in the original paper of this algorithm, this process is
  divided in two steps: first, build the basic trie and then complete it
  with the extra edges that allow us to use this trie as a DFA that recognizes
  our pattern words.
*/
void AhoCorasick::_build_automata()  {
  // The first step consists of building a Trie that accepts exactly the words
  // in our pattern list
}

AhoCorasick::AhoCorasick() {

}

AhoCorasick::AhoCorasick(std::vector< std::string > patterns) {
  set_patterns(patterns);
}

std::vector< std::vector< int > > AhoCorasick::find_matches(std::string text) {
  std::vector< std::vector< int > > ret;

  return ret;
}

/*
  This is simply a fancy wrapper that returns the same as the method above
  but in a map of the form < string, vector<int> >
*/
std::map< std::string, std::vector< int > > AhoCorasick::find_matches_map(std::string text) {
  std::vector< std::vector< int > > _ret = find_matches(text);
  std::map< std::string, std::vector< int > > ret;
  for(int i=0; i<int(_patterns.size()); ++i) {
    ret[_patterns[i]] = _ret[i];
  }
  return ret;
}

void AhoCorasick::set_patterns(std::vector< std::string > patterns) {
  _patterns = patterns;
  _build_automata();
}

const std::vector< std::string >& AhoCorasick::get_patterns() {
  return _patterns;
}
