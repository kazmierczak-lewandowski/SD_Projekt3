#include "Avl.hpp"

#include <algorithm>
#include <queue>

void AVLTree::insert(Element element) {
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
  updateBalanceUp(parent);
}

void AVLTree::deleteNode(Utils::TreeNode *node) {
  if (node == nullptr) return;

  Utils::TreeNode *parent = node->parent;

  if (node->left == nullptr && node->right == nullptr) {
    if (node == root.get()) {
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
    std::unique_ptr<Utils::TreeNode> &child = (node->left) ? node->left : node->right;
    if (node == root.get()) {
      root = std::move(child);
      root->parent = nullptr;
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
    return;
  }

  updateBalanceUp(parent);
}
bool AVLTree::findAndReplace(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  const auto newElement = Element(element.getKey(),element.getValue());
  deleteNode(node);
  insert(newElement);
  return true;
}

bool AVLTree::remove(const Element element) {
  const auto node = findElement(element);
  if (node == nullptr) {
    return false;
  }
  deleteNode(node);
  return true;
}

Utils::TreeNode *AVLTree::findElement(const Element &element) const {
  Utils::TreeNode *current = root.get();
  while (current != nullptr && current->element.getKey() != element.getKey()) {
    if (element < current->element) {
      current = current->left.get();
      continue;
    }
    current = current->right.get();
  }
  return current;
}
void AVLTree::RRRotation(std::unique_ptr<Utils::TreeNode> &current) {
  std::unique_ptr<Utils::TreeNode> currentRight = std::move(current->right);
  const auto parent = current->parent;
  const Utils::TreeNode *parentLeft = nullptr;
  const Utils::TreeNode *parentRight = nullptr;
  if (parent != nullptr) {
    if (parent->left != nullptr){
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr){
      parentRight = parent->right.get();
    }
  }
  current->right = move(currentRight->left);
  if (current->right != nullptr) {
    current->right->parent = current.get();
  }
  currentRight->left = move(current);
  const auto original = currentRight->left.get();
  currentRight->parent = parent;
  original->parent = currentRight.get();
  updateHeight(original);
  if (parent == nullptr) {
    root = std::move(currentRight);
    updateHeight(root.get());
  } else {
    if (parentLeft == original) {
      parent->left = std::move(currentRight);
      updateHeight(parent->left.get());
    } else if (parentRight == original) {
      parent->right = std::move(currentRight);
      updateHeight(parent->right.get());
    }
  }
}
void AVLTree::LLRotation(std::unique_ptr<Utils::TreeNode> &current) {
  std::unique_ptr<Utils::TreeNode> currentLeft = std::move(current->left);
  const auto parent = current->parent;
  const Utils::TreeNode *parentLeft = nullptr;
  const Utils::TreeNode *parentRight = nullptr;
  if (parent != nullptr) {
    if (parent->left != nullptr){
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr){
      parentRight = parent->right.get();
    }
  }
  current->left = move(currentLeft->right);
  if (current->left != nullptr) {
    current->left->parent = current.get();
  }
  currentLeft->right = move(current);
  const auto original = currentLeft->right.get();
  currentLeft->parent = parent;
  original->parent = currentLeft.get();
  updateHeight(original);
  if (parent == nullptr) {
    root = std::move(currentLeft);
    updateHeight(root.get());
  } else {
    if (parentLeft == original) {
      parent->left = std::move(currentLeft);
      updateHeight(parent->left.get());
    } else if (parentRight == original) {
      parent->right = std::move(currentLeft);
      updateHeight(parent->right.get());
    }
  }
}
void AVLTree::LRRotation(std::unique_ptr<Utils::TreeNode> &current) {
  RRRotation(current->left);
  LLRotation(current);
}
void AVLTree::RLRotation(std::unique_ptr<Utils::TreeNode> &current) {
  LLRotation(current->right);
  RRRotation(current);
}
int AVLTree::checkBalance(const Utils::TreeNode *current) {
  const int leftHeight = current->left ? current->left->height : -1;
  const int rightHeight = current->right ? current->right->height : -1;
  return leftHeight - rightHeight;
}
void AVLTree::balance(std::unique_ptr<Utils::TreeNode> &current) {
  if (!current)
    return;

  updateHeight(current.get());

  if (const int balance_factor = checkBalance(current.get());
      balance_factor > 1) {
    if (checkBalance(current->left.get()) >= 0) {
      LLRotation(current);
    } else {
      LRRotation(current);
    }
  } else if (balance_factor < -1) {
    if (checkBalance(current->right.get()) <= 0) {
      RRRotation(current);
    } else {
      RLRotation(current);
    }
  }
}

void AVLTree::updateHeight(Utils::TreeNode *node) {
  const int leftHeight = node->left ? node->left->height : -1;
  const int rightHeight = node->right ? node->right->height : -1;
  node->height = 1 + std::max(leftHeight, rightHeight);
}
void AVLTree::updateBalanceUp(Utils::TreeNode *node) {
  while (node != nullptr) {
    updateHeight(node);
    if (std::abs(checkBalance(node)) > 1) {
      if (node == root.get()) {
        balance(root);
        continue;
      }
      if (node->parent->left.get() == node) {
        balance(node->parent->left);
      } else {
        balance(node->parent->right);
      }
    }
    node = node->parent;
  }
}
