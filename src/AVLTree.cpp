#include "AVLTree.hpp"

#include <algorithm>
#include <queue>

void AVLTree::add(const Element element) {
  if (isEmpty()) {
    auto newNode = std::make_unique<Utils::TreeNode>(element);
    root = std::move(newNode);
    setSize(getSize() + 1);
    return;
  }
  Utils::TreeNode *parent;
  insert(element, parent);
  updateBalanceUp(parent);
}
void AVLTree::deleteNode(Utils::TreeNode *node) {
  Utils::TreeNode *parent = node->parent;

  if (node->left == nullptr && node->right == nullptr) {
    parent = removeNodeWithoutChildren(node);
  } else if (node->left == nullptr || node->right == nullptr) {
    auto &child = node->left ? node->left : node->right;
    if (node == getRoot()) {
      root = std::move(child);
      root->parent = nullptr;
    } else {
      parent = removeNodeWithOneChild(node, child);
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
void AVLTree::RRRotation(std::unique_ptr<Utils::TreeNode> &current) {
  std::unique_ptr<Utils::TreeNode> currentRight = std::move(current->right);
  const auto parent = current->parent;
  const Utils::TreeNode *parentLeft = nullptr;
  const Utils::TreeNode *parentRight = nullptr;
  if (parent != nullptr) {
    if (parent->left != nullptr) {
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr) {
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
    updateHeight(getRoot());
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
    if (parent->left != nullptr) {
      parentLeft = parent->left.get();
    }
    if (parent->right != nullptr) {
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
    updateHeight(getRoot());
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
void AVLTree::balance(Utils::TreeNode *current) {
  if (!current) return;

  updateHeight(current);
  std::unique_ptr<Utils::TreeNode> *node = nullptr;
  if (current == root.get()) {
    node = &root;
  } else if (current->parent->left.get() == current) {
    node = &current->parent->left;
  } else {
    node = &current->parent->right;
  }
  if (const int balance_factor = checkBalance(current); balance_factor > 1) {
    if (checkBalance(current->left.get()) >= 0) {
      LLRotation(*node);
    } else {
      LRRotation(*node);
    }
  } else if (balance_factor < -1) {
    if (checkBalance(current->right.get()) <= 0) {
      RRRotation(*node);
    } else {
      RLRotation(*node);
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
      if (node == getRoot()) {
        balance(node);
        continue;
      }
      if (node->parent->left.get() == node) {
        balance(node->parent->left.get());
      } else {
        balance(node->parent->right.get());
      }
    }
    node = node->parent;
  }
}
