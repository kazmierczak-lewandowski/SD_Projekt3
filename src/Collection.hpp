#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include "Element.hpp"

class Collection {
 private:
  int size = 0;

 protected:
  void setSize(const int newSize) { size = newSize; }

 public:
  virtual ~Collection() = default;
  virtual void insert(Element element) = 0;
  virtual void remove(Element element) = 0;
  int getSize() const { return size; }
};

#endif  // COLLECTION_HPP
