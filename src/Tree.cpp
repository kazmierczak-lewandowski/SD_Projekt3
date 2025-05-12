#include "Tree.hpp"
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
