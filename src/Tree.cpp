#include "Tree.hpp"

#include <functional>
void Tree::insert(Element element, Utils::TreeNode *&parent) {
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
Utils::TreeNode *Tree::findElement(const Element &element) const {
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
bool Tree::remove(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  deleteNode(node);
  return true;
}
bool Tree::findAndReplace(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  const auto newElement = Element(element.getKey(), element.getValue());
  deleteNode(node);
  insert(newElement);
  return true;
}
Utils::TreeNode *Tree::removeNodeWithoutChildren(const Utils::TreeNode *node) {
  Utils::TreeNode *parent = node->parent;
  if (node == getRoot()) {
    resetRoot();
  } else {
    if (parent->left.get() == node)
      parent->left.reset();
    else
      parent->right.reset();
  }
  setSize(getSize() - 1);
  return parent;
}
Utils::TreeNode *Tree::removeNodeWithOneChild(
    const Utils::TreeNode *node, std::unique_ptr<Utils::TreeNode> &child) {
  Utils::TreeNode *parent = node->parent;
  child->parent = parent;
  if (parent->left.get() == node)
    parent->left = std::move(child);
  else
    parent->right = std::move(child);
  return parent;
}
std::vector<Element> Tree::getAllElements() {
  std::vector<Element> elements;
  std::function<void(const Utils::TreeNode *)> inorder =
      [&](const Utils::TreeNode *node) {
        if (!node) return;
        inorder(node->left.get());
        elements.push_back(node->element);
        inorder(node->right.get());
      };
  inorder(getRoot());
  return elements;
}