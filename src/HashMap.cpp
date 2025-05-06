#include "HashMap.hpp"
HashMap::HashMap(const BucketType type) {
  using enum BucketType;
  switch (type) {
    case AVL: {
      table = std::make_unique<AVLTree[]>(CAPACITY);
      break;
    }
    case BST: {
      table = std::make_unique<BSTree[]>(CAPACITY);
      break;
    }
    case DLL: {
      table = std::make_unique<DoublyLinkedList[]>(CAPACITY);
    }
  }
}