#include "BSTree.hpp"

#include "Utils.hpp"
void BSTree::insert(Element element) {
  if (isEmpty()) {
    auto newNode = std::make_unique<Utils::TreeNode>(element);
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  Utils::TreeNode *parent;
  Tree::insert(element, parent);
}
void BSTree::deleteNode(Utils::TreeNode *node) {
  Utils::TreeNode *parent = node->parent;
  if (node->left == nullptr && node->right == nullptr) {
    removeNodeWithoutChildren(node);
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