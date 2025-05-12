#include "BSTree.hpp"

#include "Utils.hpp"
void BSTree::add(Element element) {
  if (isEmpty()) {
    auto newNode = std::make_unique<Utils::TreeNode>(element);
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  Utils::TreeNode *parent;
  insert(element, parent);
}
void BSTree::deleteNode(Utils::TreeNode *node) {
  if (node->left == nullptr && node->right == nullptr) {
    removeNodeWithoutChildren(node);
  } else if (node->left == nullptr || node->right == nullptr) {
    std::unique_ptr<Utils::TreeNode> &child =
        (node->left) ? node->left : node->right;
    if (node == getRoot()) {
      root = std::move(child);
      getRoot()->parent = nullptr;
    } else {
      removeNodeWithOneChild(node, child);
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