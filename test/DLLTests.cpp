#include <gtest/gtest.h>

#include "../src/DoublyLinkedList.hpp"
#include "../src/Element.hpp"

class DoublyLinkedListTest : public testing::Test {
 private:
  DoublyLinkedList list;

 protected:
  void SetUp() override {
    list.insert(Element{1, 10});
    list.insert(Element{2, 20});
    list.insert(Element{3, 30});
    list.insert(Element{4, 40});
  }
  DoublyLinkedList* getList() { return &list; }
};

TEST_F(DoublyLinkedListTest, InsertElementIntoEmptyList) {
  DoublyLinkedList emptyList;
  EXPECT_TRUE(emptyList.isEmpty());

  emptyList.insert(Element{5, 50});

  EXPECT_EQ(emptyList.getSize(), 1);
  EXPECT_FALSE(emptyList.isEmpty());

  const auto head = emptyList.getHead();
  const auto tail = emptyList.getTail();

  ASSERT_NE(head, nullptr);
  ASSERT_NE(tail, nullptr);

  EXPECT_EQ(head->data, Element(5, 50));
  EXPECT_EQ(tail->data, Element(5, 50));
  EXPECT_EQ(head, tail);
  EXPECT_EQ(head->prev, nullptr);
  EXPECT_EQ(head->next, nullptr);
}

TEST_F(DoublyLinkedListTest, InsertMaintainsElementOrder) {
  const auto list = getList();
  list->insert(Element{5, 50});

  EXPECT_EQ(list->getSize(), 5);
  EXPECT_EQ(list->getTail()->data, Element(5, 50));
  EXPECT_EQ(list->getTail()->prev->data, Element(4, 40));
}
TEST_F(DoublyLinkedListTest, InsertAfterElementRemove) {
  const auto list = getList();
  list->remove(Element{2, 20});
  list->insert(Element{5, 50});

  EXPECT_EQ(list->getSize(), 4);

  const auto tail = list->getTail();
  ASSERT_NE(tail, nullptr);
  EXPECT_EQ(tail->data, Element(5, 50));
  EXPECT_EQ(tail->prev->data, Element(4, 40));
}

TEST_F(DoublyLinkedListTest, ElementPointerIntegrity) {
  const auto list = getList();
  list->insert(Element{5, 50});

  auto node = list->getHead();
  while (node && node->next) {
    EXPECT_EQ(node->next->prev, node);
    EXPECT_TRUE(node->data.getKey() < node->next->data.getKey());
    node = node->next.get();
  }
}

TEST_F(DoublyLinkedListTest, RemoveNonExistentElement) {
  const auto list = getList();
  EXPECT_FALSE(list->remove(Element{99, 999}));
  EXPECT_EQ(list->getSize(), 4);
}

TEST_F(DoublyLinkedListTest, RemoveAllElements) {
  const auto list = getList();
  EXPECT_TRUE(list->remove(Element{3, 30}));
  EXPECT_TRUE(list->remove(Element{1, 10}));
  EXPECT_TRUE(list->remove(Element{2, 20}));
  EXPECT_TRUE(list->remove(Element{4, 40}));

  EXPECT_EQ(list->getSize(), 0);
  EXPECT_EQ(list->getHead(), nullptr);
  EXPECT_EQ(list->getTail(), nullptr);
}
TEST_F(DoublyLinkedListTest, RemoveElementFromTail) {
  const auto list = getList();
  EXPECT_TRUE(list->remove(Element{4, 40}));

  EXPECT_EQ(list->getSize(), 3);
  EXPECT_NE(list->getTail(), nullptr);
  EXPECT_EQ(list->getTail()->data, Element(3, 30));
  EXPECT_EQ(list->getTail()->next, nullptr);
}
TEST_F(DoublyLinkedListTest, FindAndReplaceExistingElement) {
  const auto list = getList();
  const Element newElement{3, 300};
  EXPECT_TRUE(list->findAndReplace(newElement));

  EXPECT_EQ(list->getSize(), 4);
}

TEST_F(DoublyLinkedListTest, FindAndReplaceNonExistentElement) {
  const auto list = getList();
  const Element nonExistent{99, 999};
  EXPECT_FALSE(list->findAndReplace(nonExistent));
  EXPECT_EQ(list->getSize(), 4);
}

TEST_F(DoublyLinkedListTest, FindAndReplaceUpdatesCorrectNode) {
  const auto list = getList();
  const Element updated{2, 222};
  EXPECT_TRUE(list->findAndReplace(updated));

  auto node = list->getHead();
  bool found = false;
  while (node) {
    if (node->data == updated) {
      found = true;
      EXPECT_EQ(node->data.getValue(), 222);
      break;
    }
    node = node->next.get();
  }
  EXPECT_TRUE(found);
}
TEST_F(DoublyLinkedListTest, FindAll) {
  const auto list = getList();
  const auto elements = list->getAllElements();
  ASSERT_EQ(elements.size(), 4);
  EXPECT_EQ(elements[0], Element(1, 10));
  EXPECT_EQ(elements[1], Element(2, 20));
  EXPECT_EQ(elements[2], Element(3, 30));
  EXPECT_EQ(elements[3], Element(4, 40));
}
TEST(DoublyLinkedListStandaloneTest, FindAndReplaceOnEmptyList) {
  DoublyLinkedList emptyList;
  EXPECT_FALSE(emptyList.findAndReplace(Element{1, 100}));
  EXPECT_EQ(emptyList.getSize(), 0);
}
