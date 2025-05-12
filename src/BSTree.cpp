#include "BSTree.hpp"

#include "Utils.hpp"
void BSTree::insert(Element element) {
  auto newNode = std::make_unique<Utils::TreeNode>(element);
  if (isEmpty()) {
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  auto current = root.get();
  Utils::TreeNode *parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (newNode->element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  newNode->parent = parent;
  if (parent != nullptr) {
    if (newNode->element < parent->element) {
      parent->left = std::move(newNode);
    } else {
      parent->right = std::move(newNode);
    }
  }
  setSize(getSize() + 1);
}