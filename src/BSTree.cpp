#include "BSTree.hpp"

#include "Utils.hpp"
void BSTree::insert(Element element) {
  auto newNode = std::make_unique<Utils::TreeNode>(element);
  if (isEmpty()) {
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  auto current = getRoot();
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
void BSTree::deleteNode(Utils::TreeNode *node) {

  Utils::TreeNode *parent = node->parent;

  if (node->left == nullptr && node->right == nullptr) {
    if (node == getRoot()) {
      root.reset();
    } else {
      if (parent->left.get() == node)
        parent->left.reset();
      else
        parent->right.reset();
    }
    setSize(getSize() - 1);
  }

  else if (node->left == nullptr || node->right == nullptr) {
    std::unique_ptr<Utils::TreeNode> &child =
        (node->left) ? node->left : node->right;
    if (node == getRoot()) {
      root = std::move(child);
      getRoot()->parent = nullptr;
    } else {
      child->parent = parent;
      if (parent->left.get() == node)
        parent->left = std::move(child);
      else
        parent->right = std::move(child);
    }
    setSize(getSize() - 1);
  }

  else {
    Utils::TreeNode *successor = node->right.get();
    while (successor->left) successor = successor->left.get();
    node->element = successor->element;
    deleteNode(successor);
  }
}

bool BSTree::remove(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  deleteNode(node);
  return true;
}