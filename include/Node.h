#include <vector>
const char FAIL = 0x00;

class Node {
private:
  std::unordered_map< char, Node* > _trie_adj;
  std::vector< int > _output;
public:
  Node(const std::vector< int > output);
  void add_output(int value);
  Node* get_next_node(char c);
};
