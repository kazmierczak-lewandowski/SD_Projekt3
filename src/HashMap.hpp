#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <ncurses.h>

#include <cmath>
#include <fstream>
#include <memory>

#include "Collection.hpp"
#include "Element.hpp"
enum class BucketType { AVL, BST, DLL };
class HashMap {
 private:
  std::unique_ptr<Collection[]> table;
  static constexpr int CAPACITY = 100'000;
  int hashBase();
  int hashAlt();

 public:
  explicit HashMap(BucketType type);
  void insert(Element element);
  void remove(Element element);
};

#endif  // HASHMAP_HPP
