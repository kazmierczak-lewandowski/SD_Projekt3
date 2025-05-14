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
  static constexpr int CAPACITY = 10'000;
  static constexpr int A = 1'234'567;
  static constexpr int B = 987'654;
  static constexpr int P = 5'000'003;
  static int hashBase(int key);
  static int hashAlt(int key);

 public:
  explicit HashMap(BucketType type);
  void insert(Element element);
  bool remove(Element element);
  [[nodiscard]] int getBucketSize(const int index) const {
    return table[index]->getSize();
  }
  void print() const;
  static void fillWithRandom(const std::unique_ptr<HashMap> &collection,
                             int size);
  static void fillFromFile(HashMap &map, const std::string &filename, int size);
  [[nodiscard]] std::vector<Element> getAllElements() const;
  [[nodiscard]] Element getRandomElement() const;
};

#endif  // HASHMAP_HPP
