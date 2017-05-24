#include "AhoCorasick.h"

Node* AhoCorasick::_trie_insert(Node* root, std::string w, int index, int output_index) {
  if(root == NULL) {
    root = new Node();
    root->adj = std::vector< Node* >(AhoCorasick::ALPHABET_SIZE, NULL);
  }
  if(index == int(w.size())) {
    root->output.insert(output_index);
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
  // in our pattern list (Algorithm 2 in original paper)
  _root = NULL;
  for(int i=0; i<int(_patterns.size()); ++i) {
    // _trie_insert is equivalent to procedure "enter" explained in Algorithm 2
    // in original paper
    _root = _trie_insert(_root, _patterns[i], 0, i);
  }
  for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
    if(_root->adj[i] == NULL) _root->adj[i] = _root;
  }
  _root->fail = _root;
  // As a second step, we must build the failure function
  // This part of code corresponds to the one explained in Algorithm 3
  std::queue< Node* > Q;

  for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
    if(_root->adj[i] != NULL && _root->adj[i] != _root) {
      Q.push(_root->adj[i]);
      _root->adj[i]->fail = _root;
    }
  }

  while(!Q.empty()) {
    Node* v = Q.front();
    Q.pop();
    for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
      if(v->adj[i] != NULL) {
        Q.push(v->adj[i]);
        Node* state = v->fail;
        while(state->adj[i] == NULL) state = state->fail;
        v->adj[i]->fail = state->adj[i];
        // merge the outputs of the adjacent state to its fail state
        v->adj[i]->output.insert(v->adj[i]->fail->output.begin(),
                                 v->adj[i]->fail->output.end());
      }
    }
  }
}

AhoCorasick::AhoCorasick() {

}

AhoCorasick::~AhoCorasick() {

}

AhoCorasick::AhoCorasick(std::vector< std::string > patterns) {
  set_patterns(patterns);
}

/*
  This method uses the previously built automata to find all the
  matches of the patterns on a given string
*/
std::vector< std::vector< int > > AhoCorasick::find_matches(std::string text) {
  std::vector< std::vector< int > > ret(int(_patterns.size()), std::vector< int >());

  Node* current_state = _root;

  for(int i=0; i<int(text.size()); ++i) {
    // add all outputs of the current state as matches

    if(current_state->adj[text[i]] != NULL) {
      current_state = current_state->adj[text[i]];
    }
    else {
      current_state = current_state->fail;
    }
    for(int outp : current_state->output) {
        ret[outp].push_back(i);
    }
  }

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


void AhoCorasick::print_dot_automata() {
  std::cout << "digraph AhoCorasickAutomata {" << std::endl;
  std::queue< Node* > Q;
  Q.push(_root);
  while(!Q.empty()) {
    Node* v = Q.front();
    Q.pop();
    std::cout << "\"" << v << "\"" << " -> " << "\"" << v->fail <<  "\"" <<" [label=\"#\"];" << std::endl;
    for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
      if(v->adj[i] != NULL && v->adj[i] != _root) {
        Q.push(v->adj[i]);
        std::cout << "\"" << v << "\"" << " -> " << "\"" << v->adj[i] << "\"" << " [label=\"" << char(i) << "\"];" << std::endl;
      }
    }
  }
  std::cout << "}" << std::endl;
}
