#include "Trie.h"

Trie::Node* Trie::_insert_word(Trie::Node* root, std::string w, int index, int output_index) {
  if(root == NULL) {
    root = new Trie::Node();
    root->adj = std::vector< Trie::Node* >(Trie::ALPHABET_SIZE, NULL);
  }
  if(index == int(w.size())) {
    root->output.insert(output_index);
  } else {
    root->adj[w[index]] = _insert_word(root->adj[w[index]], w, index+1, output_index);
  }
  return root;
}

void Trie::_erase_tree(Trie::Node* root) {
  if(root == NULL) return;
  for(int i = 0; i<int(root->adj.size()); ++i) {
    _erase_tree(root->adj[i]);
  }
  delete root;
}

Trie::~Trie() {
  _erase_tree(_root);
}

Trie::Trie(std::vector< std::string >& patterns) : Matcher(patterns) {
  _root = NULL;
  _patterns = patterns;
  for(int i=0; i<int(_patterns.size()); ++i) {
    _root = _insert_word(_root, _patterns[i], 0, i);
  }
}

std::vector< std::vector< int > > Trie::find_matches(std::string& text) {
  std::vector< std::vector< int > > ret(int(_patterns.size()), std::vector< int >());
  for(int i=0; i<int(text.size()); ++i) {
    Trie::Node* current = _root;
    int j = i;
    while(j < int(text.size()) && current != NULL) {
      current = current->adj[text[j]];
      if(current != NULL) {
        for(int outp : current->output) ret[outp].push_back(i);
      }
      ++j;
    }
  }
  return ret;
}
