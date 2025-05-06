#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <ncurses.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Collection.hpp"
#include "Element.hpp"
#include "Utils.hpp"
enum class BucketType { AVL, BST, DLL };
class HashMap {
 private:
  std::unique_ptr<Collection[]> table;
  constexpr int CAPACITY = 100'000;
  int hashBase();
  int hashAlt();

 public:
  explicit HashMap(BucketType type);
  void insert(Element element);
  void remove(Element element);
};

#endif  // HASHMAP_HPP
