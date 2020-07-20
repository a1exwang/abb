#include <stack>
#include <iostream>

#include "binary_tree.hpp"

void dfs(Node *root) {
  std::stack<Node*> stack;
  stack.push(root);

  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    if (node) {
      std::cout << node->data << std::endl;
      stack.push(node->right);
      stack.push(node->left);
    }
  }
}

int main() {
  std::vector<int> level_order= {
      0,1,2,-1,-1,5,6
  };
  auto root = build_tree(level_order);
  dfs(root);

}