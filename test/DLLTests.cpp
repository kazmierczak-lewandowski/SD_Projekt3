#include <gtest/gtest.h>
#include "../src/DoublyLinkedList.hpp"
#include "../src/Element.hpp"

class DoublyLinkedListTest : public testing::Test {
protected:
    void SetUp() override {
        list.insert(Element{1, 10});
        list.insert(Element{2, 20});
        list.insert(Element{3, 30});
        list.insert(Element{4, 40});
    }

    DoublyLinkedList list;
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
    list.insert(Element{5, 50});

    EXPECT_EQ(list.getSize(), 5);
    EXPECT_EQ(list.getTail()->data, Element(5, 50));
    EXPECT_EQ(list.getTail()->prev->data, Element(4, 40));
}
TEST_F(DoublyLinkedListTest, InsertAfterElementRemove) {
    list.remove(Element{2, 20});
    list.insert(Element{5, 50});

    EXPECT_EQ(list.getSize(), 4);

    const auto tail = list.getTail();
    ASSERT_NE(tail, nullptr);
    EXPECT_EQ(tail->data, Element(5, 50));
    EXPECT_EQ(tail->prev->data, Element(4, 40));
}

TEST_F(DoublyLinkedListTest, ElementPointerIntegrity) {
    list.insert(Element{5, 50});

    auto node = list.getHead();
    while (node && node->next) {
        EXPECT_EQ(node->next->prev, node);
        EXPECT_TRUE(node->data.getKey() < node->next->data.getKey());
        node = node->next.get();
    }
}

TEST_F(DoublyLinkedListTest, RemoveNonExistentElement) {
    EXPECT_FALSE(list.remove(Element{99, 999}));
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(DoublyLinkedListTest, RemoveAllElements) {
    EXPECT_TRUE(list.remove(Element{1, 10}));
    EXPECT_TRUE(list.remove(Element{2, 20}));
    EXPECT_TRUE(list.remove(Element{3, 30}));
    EXPECT_TRUE(list.remove(Element{4, 40}));

    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getTail(), nullptr);
}
