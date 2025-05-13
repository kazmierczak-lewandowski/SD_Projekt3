#include "HashMap.hpp"

#include "AVLTree.hpp"
#include "BSTree.hpp"
#include "DoublyLinkedList.hpp"
int HashMap::hashBase(const int key) { return ((A * key + B) % P) % CAPACITY; }
int HashMap::hashAlt(const int key) { return key % CAPACITY; }
HashMap::HashMap(const BucketType type) {
  using enum BucketType;
  switch (type) {
    case AVL: {
      table = std::make_unique<std::unique_ptr<Collection>[]>(CAPACITY);
      for (size_t i = 0; i < CAPACITY; ++i) {
        table[i] = std::make_unique<AVLTree>();
      }
      break;
    }
    case BST: {
      table = std::make_unique<std::unique_ptr<Collection>[]>(CAPACITY);
      for (size_t i = 0; i < CAPACITY; ++i) {
        table[i] = std::make_unique<BSTree>();
      }
      break;
    }
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

  const std::unique_ptr<Collection>& tableBase = table[hashBase];
  const std::unique_ptr<Collection>& tableAlt = table[hashAlt];

  if (tableBase->findAndReplace(element) ||
      tableAlt->findAndReplace(element)) {
    return;
  }
  if (tableBase->getSize() <= tableAlt->getSize()) {
    tableBase->insert(element);
    return;
  }
  tableAlt->insert(element);
}
bool HashMap::remove(const Element element) {
  if (table[hashBase(element.getKey())]->remove(element)) {
    return true;
  }
  return table[hashAlt(element.getKey())]->remove(element);
}
void HashMap::fillFromFile(HashMap& map, const std::string& filename,
                           const int size) {
  std::ifstream ifs(filename);
  int number;
  int priority;
  int i = 0;
  while (ifs >> number && ifs >> priority) {
    if (i > size) {
      break;
    }
    const auto element = Element(number, priority);
    map.insert(element);
    i++;
  }
  ifs.close();
}