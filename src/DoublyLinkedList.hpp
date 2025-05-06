#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP
#include <memory>

#include "Collection.hpp"
class DoublyLinkedList final : public Collection {
 private:
  struct Node {
    std::unique_ptr<Node> next = nullptr;  ///< Pointer to the next node.
    Node *prev = nullptr;                  ///< Pointer to the previous node.
    Element data;                              ///< Data stored in the node.
    explicit Node(const Element element) : data(element) {}
  };
  std::unique_ptr<Node> head = nullptr;  ///< Pointer to the first node.
  Node *tail = nullptr;                  ///< Pointer to the last node.
  Node* find(Element element) const;
 public:
  void insert(Element element) override;
  bool remove(Element element) override;
  bool findAndReplace(Element element) override;
  Node *getHead() const {
    return head.get();
  }
  Node *getTail() const {
    return tail;
  }
};

#endif  // DOUBLYLINKEDLIST_HPP
