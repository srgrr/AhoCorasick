#include "AhoCorasick.h"

Node* AhoCorasick::_trie_insert(Node* root, std::string w, int index, int output_index) {
  if(root == NULL) {
    root = new Node();
    root->adj = std::vector< Node* >(AhoCorasick::ALPHABET_SIZE, NULL);
  }
  if(index == int(w.size())) {
    root->output.push_back(output_index);
  } else {
    root->adj[w[index]] = _trie_insert(root->adj[w[index]], w, index+1, output_index);
  }
  return root;
}

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
  // in our pattern list (Algorithm 1 in original paper)
  _root = NULL;
  for(int i=0; i<int(_patterns.size()); ++i) {
    // _trie_insert is equivalent to procedure "enter" explained in algorithm 1
    // in original paper
    _root = _trie_insert(_root, _patterns[i], 0, i);
  }
  _root->fail = _root;

  // As a second step, we must build the failure function
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
