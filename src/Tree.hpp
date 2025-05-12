#ifndef TREE_HPP
#define TREE_HPP
#include "Collection.hpp"
#include "Utils.hpp"

class Tree : public Collection {
 protected:
  virtual void deleteNode(Utils::TreeNode *node) = 0;
  virtual void resetRoot() = 0;
 public:
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
  Utils::TreeNode* removeNodeWithoutChildren(const Utils::TreeNode* node);
  static Utils::TreeNode* removeNodeWithOneChild(
      const Utils::TreeNode* node, std::unique_ptr<Utils::TreeNode>& child);
  void insert(Element element, Utils::TreeNode*& parent);
  virtual void insert(Element element) = 0;
  [[nodiscard]] Utils::TreeNode* findElement(
      const Element &element) const;
  [[nodiscard]] virtual Utils::TreeNode* getRoot() const = 0;
};

#endif  // TREE_HPP
