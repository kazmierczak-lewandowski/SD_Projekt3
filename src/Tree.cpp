#include "Tree.hpp"
void Tree::insert(Element element, Utils::TreeNode*& parent) {
  auto newNode = std::make_unique<Utils::TreeNode>(element);
  auto current = getRoot();
  parent = nullptr;
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
Utils::TreeNode* Tree::findElement(const Element &element) const {
  Utils::TreeNode *current = getRoot();
  while (current != nullptr && current->element.getKey() != element.getKey()) {
    if (element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  return current;
}
bool Tree::findAndReplace(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  const auto newElement = Element(element.getKey(),element.getValue());
  deleteNode(node);
  insert(newElement);
  return true;
}
