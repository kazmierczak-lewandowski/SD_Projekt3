#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include <vector>

#include "Element.hpp"
class Collection {
 private:
  int size = 0;

 protected:
  void setSize(const int newSize) { size = newSize; }

 public:
  virtual ~Collection() = default;
  virtual void insert(Element element) = 0;
  virtual bool remove(Element element) = 0;
  virtual bool findAndReplace(Element element) = 0;
  [[nodiscard]] int getSize() const { return size; }
  [[nodiscard]] bool isEmpty() const { return size == 0; }
  virtual std::vector<Element> getAllElements() = 0;
};

#endif  // COLLECTION_HPP
