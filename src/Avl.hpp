#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Collection.hpp"
#include "Utils.hpp"

class AVLTree final : public Collection {
private:
  std::unique_ptr<Utils::TreeNode> root = nullptr;
  void LLRotation(std::unique_ptr<Utils::TreeNode> &current);
  void RRRotation(std::unique_ptr<Utils::TreeNode> &current);
  void LRRotation(std::unique_ptr<Utils::TreeNode> &current);
  void RLRotation(std::unique_ptr<Utils::TreeNode> &current);
  static int checkBalance(const Utils::TreeNode *current);
  void balance(std::unique_ptr<Utils::TreeNode> &current);
  static void updateHeight(Utils::TreeNode *node);
  void updateBalanceUp(Utils::TreeNode *node);
  void deleteNode(Utils::TreeNode *node);

public:
  explicit AVLTree() = default;
  ~AVLTree() override = default;
  void insert(Element element) override;
  [[nodiscard]] Utils::TreeNode* findElement(const Element &element) const;
  [[nodiscard]] Utils::TreeNode* getRoot() const {
    return root.get();
  }
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
};

#endif // AVLTree_HPP
