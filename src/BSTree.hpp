#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <memory>

#include "Collection.hpp"

class BSTree final : public Collection {
 private:
 public:
  void insert(Element element) override;
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
};

#endif  // BSTREE_HPP
