#ifndef TREE_HPP
#define TREE_HPP
#include "Collection.hpp"
#include "Utils.hpp"

class Tree : public Collection {
 protected:
  virtual void deleteNode(Utils::TreeNode *node) = 0;
 public:
  bool findAndReplace(Element element) override;
  void insert(Element element, Utils::TreeNode*& parent);
  void insert(Element element) override = 0;
  [[nodiscard]] Utils::TreeNode* findElement(
      const Element &element) const;
  [[nodiscard]] virtual Utils::TreeNode* getRoot() const = 0;
};

#endif  // TREE_HPP
