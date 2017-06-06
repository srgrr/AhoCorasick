#include "AhoCorasick.h"

AhoCorasick::Node* AhoCorasick::_trie_insert(AhoCorasick::Node* root, std::string w, int index, int output_index) {
  if(root == NULL) {
    root = new AhoCorasick::Node();
    root->adj = std::vector< AhoCorasick::Node* >(AhoCorasick::ALPHABET_SIZE, NULL);
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
  std::queue< AhoCorasick::Node* > Q;

  for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
    if(_root->adj[i] != NULL && _root->adj[i] != _root) {
      Q.push(_root->adj[i]);
      _root->adj[i]->fail = _root;
    }
  }

  while(!Q.empty()) {
    AhoCorasick::Node* v = Q.front();
    Q.pop();
    for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
      if(v->adj[i] != NULL) {
        Q.push(v->adj[i]);
        AhoCorasick::Node* state = v->fail;
        while(state->adj[i] == NULL) state = state->fail;
        v->adj[i]->fail = state->adj[i];
        // merge the outputs of the adjacent state to its fail state
        v->adj[i]->output.insert(v->adj[i]->fail->output.begin(),
                                 v->adj[i]->fail->output.end());
      }
    }
  }
}

void AhoCorasick::_erase_tree(AhoCorasick::Node* root) {
  if(root == NULL) return;
  for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
    if(root->adj[i] != root) {
      _erase_tree(root->adj[i]);
    }
  }
  delete root;
}

AhoCorasick::~AhoCorasick() {
  _erase_tree(_root);
}


void AhoCorasick::_set_patterns(std::vector< std::string >& patterns) {
  _patterns = patterns;
  _build_automata();
}

AhoCorasick::AhoCorasick(std::vector< std::string >& patterns) : Matcher(patterns) {
  _set_patterns(patterns);
}

/*
  This method uses the previously built automata to find all the
  matches of the patterns on a given string
*/
std::vector< std::vector< int > > AhoCorasick::find_matches(std::string& text) {
  std::vector< std::vector< int > > ret(int(_patterns.size()), std::vector< int >());

  AhoCorasick::Node* current_state = _root;

  for(int i=0; i<int(text.size()); ++i) {
    // this step comes from the paragraph that begins with
    // "The failure function produced by Algorithm 3 is not optimal..."
    // Basically, you must perform a KMP-like failure iteration
    // It must be noted that the cost of this function is still linear
    // since current_state can be "backed" O(|d|) times and it is
    // "moved" forward just one time per iteration
    while(current_state->adj[text[i]] == NULL) {
      current_state = current_state->fail;
    }
    // Advance to the proper state
    current_state = current_state->adj[text[i]];
    // Add all the found occurrences
    for(int outp : current_state->output) {
        ret[outp].push_back(i - int(_patterns[outp].size()) + 1);
    }
  }

  return ret;
}

void AhoCorasick::_label_automata(AhoCorasick::Node* root, std::string pref) {
  _label_map[root] = pref;
  for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
    if(root->adj[i] != NULL && root->adj[i] != root) {
      _label_automata(root->adj[i], pref + char(i));
    }
  }
}

void AhoCorasick::print_dot_automata() {
  _label_map.clear();
  _label_automata(_root, "");
  std::cout << "digraph AhoCorasickAutomata {" << std::endl;
  std::queue< AhoCorasick::Node* > Q;
  Q.push(_root);
  while(!Q.empty()) {
    AhoCorasick::Node* v = Q.front();
    Q.pop();
    std::cout << "\"" << _label_map[v] << "\"" << " -> " << "\"" << _label_map[v->fail] <<  "\"" <<" [label=\"#\"];" << std::endl;
    for(int i=0; i<AhoCorasick::ALPHABET_SIZE; ++i) {
      if(v->adj[i] != NULL && v->adj[i] != _root) {
        Q.push(v->adj[i]);
        std::cout << "\"" << _label_map[v] << "\"" << " -> " << "\"" << _label_map[v->adj[i]] << "\"" << " [label=\"" << char(i) << "\"];" << std::endl;
      }
    }
  }
  std::cout << "}" << std::endl;
}
