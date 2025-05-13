#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <memory>

#include "Tree.hpp"
#include "Utils.hpp"

class BSTree final : public Tree {
 private:
  std::unique_ptr<Utils::TreeNode> root = nullptr;
  void deleteNode(Utils::TreeNode* node) override;

 protected:
  void resetRoot() override { root.reset(); };

 public:
  void add(Element element) override;
  [[nodiscard]] Utils::TreeNode* getRoot() const override { return root.get(); }
};

#endif  // BSTREE_HPP
