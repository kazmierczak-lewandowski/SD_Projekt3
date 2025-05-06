#include "DoublyLinkedList.hpp"
DoublyLinkedList::Node *DoublyLinkedList::find(const Element element) const {
  Node *currentFront = head.get();
  Node *currentBack = tail;
  int itFront = 0;
  int itBack = getSize() - 1;
  while (itFront <= itBack) {
    if (currentFront->data.checkKey(element)) {
      return currentFront;
    }
    if (currentBack->data.checkKey(element)) {
      return currentBack;
    }
    currentFront = currentFront->next.get();
    itFront++;

    currentBack = currentBack->prev;
    itBack--;
  }
  return nullptr;
}
void DoublyLinkedList::insert(Element element) {
  auto newNode = std::make_unique<Node>(element);
  if (isEmpty()) {
    head = std::move(newNode);
    tail = head.get();
    setSize(getSize() + 1);
    return;
  }
  newNode->prev = tail;
  tail->next = std::move(newNode);
  tail = tail->next.get();
  setSize(getSize() + 1);
}
bool DoublyLinkedList::remove(const Element element) {
  if (isEmpty()) {
    return false;
  }
  if (getSize() == 1) {
    head = nullptr;
    tail = nullptr;
    setSize(getSize() - 1);
    return true;
  }
  if (element == head->data) {
    head->next->prev = nullptr;
    head = std::move(head->next);
    setSize(getSize() - 1);
    return true;
  }
  if (element == tail->data) {
    tail = tail->prev;
    tail->next = nullptr;
    setSize(getSize() - 1);
    return true;
  }
  Node *current = find(element);
  if (current == nullptr) return false;
  current = current->prev;
  current->next->next->prev = current;
  current->next = std::move(current->next->next);
  setSize(getSize() - 1);
  return true;
}
bool DoublyLinkedList::findAndReplace(const Element element) {
        Node *current = find(element);
        if (current == nullptr) return false;
        current->data = element;
        return true;
}