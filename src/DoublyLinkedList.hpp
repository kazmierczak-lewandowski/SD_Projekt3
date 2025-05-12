#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP
#include <memory>

#include "Collection.hpp"
class DoublyLinkedList final : public Collection {
 private:
  struct Node {
    std::unique_ptr<Node> next = nullptr;
    Node *prev = nullptr;
    Element data;
    explicit Node(const Element element) : data(element) {}
  };
  std::unique_ptr<Node> head = nullptr;
  Node *tail = nullptr;
  [[nodiscard]] Node *find(Element element) const;

 public:
  void insert(Element element) override;
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
  [[nodiscard]] Node *getHead() const {
    return head.get();
  }
  [[nodiscard]] Node *getTail() const {
    return tail;
  }
};

#endif  // DOUBLYLINKEDLIST_HPP
