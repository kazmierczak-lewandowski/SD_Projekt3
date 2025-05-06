#include "HashMap.hpp"
int HashMap::hashBase(const int key) { return ((A * key + B) % P) % CAPACITY; }
int HashMap::hashAlt(const int key) { return key % CAPACITY; }
HashMap::HashMap(const BucketType type) {
  using enum BucketType;
  switch (type) {
    // case AVL: {
    //   table = std::make_unique<AVLTree[]>(CAPACITY);
    //   break;
    // }
    // case BST: {
    //   table = std::make_unique<BSTree[]>(CAPACITY);
    //   break;
    // }
    // case DLL: {
    //   table = std::make_unique<DoublyLinkedList[]>(CAPACITY);
    // }
  }
}
void HashMap::insert(const Element element) {
  const int hashBase = HashMap::hashBase(element.getKey());
  const int hashAlt = HashMap::hashAlt(element.getKey());
  if (table[hashBase].getSize() < table[hashAlt].getSize()) {
    table[hashBase].insert(element);
    return;
  }
  table[hashAlt].insert(element);
}