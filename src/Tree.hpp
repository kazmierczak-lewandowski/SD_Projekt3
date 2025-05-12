#ifndef TREE_HPP
#define TREE_HPP
#include "Collection.hpp"
#include "Utils.hpp"

class Tree : public Collection {
 protected:
  virtual void deleteNode(Utils::TreeNode *node) = 0;
 public:
  bool findAndReplace(Element element) override;
  [[nodiscard]] Utils::TreeNode* findElement(
      const Element &element) const;
  [[nodiscard]] virtual Utils::TreeNode* getRoot() const = 0;
};

#endif  // TREE_HPP
