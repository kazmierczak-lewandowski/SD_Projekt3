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
  std::vector<Element> getAllElements();
  void insert(Element element, Utils::TreeNode*& parent);
  void insert(const Element element) override {
    add(element);
  };
  virtual void add(Element element) = 0;
  [[nodiscard]] Utils::TreeNode* findElement(
      const Element &element) const;
  [[nodiscard]] virtual Utils::TreeNode* getRoot() const = 0;
};

#endif  // TREE_HPP
