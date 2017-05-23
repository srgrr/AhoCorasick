#include "Node.h"

Node::Node(const std::vector<int> output) {

}

void Node::add_output(int value) {
  _output.push_back(value);
}

Node* Node::get_next_node(char c) {
  return _trie_adj[c];
}
