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
  std::unique_ptr<std::unique_ptr<Collection>[]> table;
  static constexpr int CAPACITY = 100'000;
  static constexpr int A = 1'234'567;
  static constexpr int B = 987'654;
  static constexpr int P = 5'000'003;
  static int hashBase(int key);
  static int hashAlt(int key);

 public:
  explicit HashMap(BucketType type);
  void insert(Element element);
  void remove(Element element);
};

#endif  // HASHMAP_HPP
