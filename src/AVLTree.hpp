#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Tree.hpp"
#include "Utils.hpp"

class AVLTree final : public Tree {
 private:
  std::unique_ptr<Utils::TreeNode> root = nullptr;
  void LLRotation(std::unique_ptr<Utils::TreeNode> &current);
  void RRRotation(std::unique_ptr<Utils::TreeNode> &current);
  void LRRotation(std::unique_ptr<Utils::TreeNode> &current);
  void RLRotation(std::unique_ptr<Utils::TreeNode> &current);
  static int checkBalance(const Utils::TreeNode *current);
  void balance(Utils::TreeNode *current);
  static void updateHeight(Utils::TreeNode *node);
  void updateBalanceUp(Utils::TreeNode *node);
  void deleteNode(Utils::TreeNode *node) override;

 public:
  ~AVLTree() override = default;
  void insert(Element element) override;
  [[nodiscard]] Utils::TreeNode *getRoot() const override {
    return root.get();
  };
};

#endif  // AVLTree_HPP
