#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <memory>

#include "Collection.hpp"
#include "Utils.hpp"

class BSTree final : public Collection {
 private:
  std::unique_ptr<Utils::TreeNode> root = nullptr;
  void deleteNode(Utils::TreeNode* node);
 public:
  void insert(Element element) override;
  [[nodiscard]] Utils::TreeNode* findElement(const Element& element) const;
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
};

#endif  // BSTREE_HPP
