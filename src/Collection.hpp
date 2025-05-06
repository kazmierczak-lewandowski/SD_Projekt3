#ifndef COLLECTION_HPP
#define COLLECTION_HPP

class Collection {
 private:
  int size = 0;

 protected:
  void setSize(const int newSize) { size = newSize; }

 public:
  virtual ~Collection() = default;
  virtual void insert() = 0;
  virtual void remove() = 0;
};

#endif  // COLLECTION_HPP
