#include "HashMap.hpp"

#include "DoublyLinkedList.hpp"
int HashMap::hashBase(const int key) { return ((A * key + B) % P) % CAPACITY; }
int HashMap::hashAlt(const int key) { return key % CAPACITY; }
HashMap::HashMap(const BucketType type) {
  using enum BucketType;
  switch (type) {
    // case AVL: {
    //   table = std::make_unique<std::unique_ptr<Collection>[]>(CAPACITY);
    //   for (size_t i = 0; i < CAPACITY; ++i) {
    //     table[i] = std::make_unique<AVLTree[]>();
    //   }
    //   break;
    // }
    // case BST: {
    //   table = std::make_unique<std::unique_ptr<Collection>[]>(CAPACITY);
    //   for (size_t i = 0; i < CAPACITY; ++i) {
    //     table[i] = std::make_unique<BSTree[]>();
    //   }
    //   break;
    // }
    case DLL: {
      table = std::make_unique<std::unique_ptr<Collection>[]>(CAPACITY);
      for (size_t i = 0; i < CAPACITY; ++i) {
        table[i] = std::make_unique<DoublyLinkedList>();
      }
    }
  }
}
void HashMap::insert(const Element element) {
  const int hashAlt = HashMap::hashAlt(element.getKey());
  const int hashBase = HashMap::hashBase(element.getKey());

  if (table[hashBase]->findAndReplace(element) ||
      table[hashAlt]->findAndReplace(element)) {
    return;
  }
  if (table[hashBase]->getSize() < table[hashAlt]->getSize()) {
    table[hashBase]->insert(element);
    return;
  }
  table[hashAlt]->insert(element);
}
void HashMap::remove(const Element element) {
  if (table[HashMap::hashBase(element.getKey())]->remove(element)) {
    return;
  }
  table[HashMap::hashAlt(element.getKey())]->remove(element);
}