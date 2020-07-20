#pragma once
#include <cassert>

#include <vector>
#include <queue>


struct Node {
  Node(int value) :data(value) { }
  Node *left = nullptr;
  Node *right = nullptr;
  int data;
};

Node *build_tree(std::vector<int> level_order) {
  assert(level_order.size() % 2 == 1);
  Node *root = nullptr;
  if (level_order[0] != -1) {
    root = new Node(level_order[0]);
  }

  std::queue<Node*> q;
  q.push(root);
  int i = 1;
  while (i < level_order.size()) {
    auto node = q.front();
    q.pop();

    if (!node) {
      q.push(nullptr);
      q.push(nullptr);
    } else {
      if (level_order[i] != -1) {
        node->left = new Node(level_order[i]);
      }
      q.push(node->left);
      if (level_order[i+1] != -1) {
        node->right = new Node(level_order[i+1]);
      }
      q.push(node->right);
    }
    i += 2;
  }
  return root;
}