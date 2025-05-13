#include "../src/BSTree.hpp"
#include <gtest/gtest.h>

class BSTreeTest : public ::testing::Test {
private:
  BSTree tree;
  
protected:
  BSTree* getTree() {
    return &tree;
  }
  void SetUp() override {
    tree.insert(Element(10, 10));
    tree.insert(Element(5, 5));
    tree.insert(Element(15, 15));
  }
};

TEST_F(BSTreeTest, FindExistingElement) {
  EXPECT_NE(getTree()->findElement(Element(10, 10)), nullptr);
}

TEST_F(BSTreeTest, FindNonExistentElement) {
  EXPECT_EQ(getTree()->findElement(Element(20, 30)), nullptr);
}

TEST_F(BSTreeTest, RemoveExistingElement) {
  EXPECT_TRUE(getTree()->remove(Element(10, 10)));
  EXPECT_EQ(getTree()->getSize(), 2);
  EXPECT_EQ(getTree()->findElement(Element(10, 10)), nullptr);
}

TEST_F(BSTreeTest, RemoveNonExistentElement) {
  EXPECT_FALSE(getTree()->remove(Element(20, 20)));
  EXPECT_EQ(getTree()->getSize(), 3);
}

TEST_F(BSTreeTest, ReplaceExistingElement) {
  EXPECT_TRUE(getTree()->findAndReplace(Element(10, 30)));
  EXPECT_EQ(getTree()->getSize(), 3);
  EXPECT_NE(getTree()->findElement(Element(10, 30)), nullptr);
  EXPECT_EQ(getTree()->findElement(Element(10, 30))->element.getValue(), 30);
}

TEST_F(BSTreeTest, ReplaceNonExistentElement) {
  EXPECT_FALSE(getTree()->findAndReplace(Element(20, 30)));
  EXPECT_EQ(getTree()->getSize(), 3);
}
TEST_F(BSTreeTest, RemoveFromEmptyTree) {
  BSTree emptyTree;
  EXPECT_FALSE(emptyTree.remove(Element(10, 20)));
  EXPECT_EQ(emptyTree.getSize(), 0);
}

TEST_F(BSTreeTest, RemoveFromSingleElementTree) {
  BSTree singleElementTree;
  singleElementTree.insert(Element(10, 1));
  EXPECT_TRUE(singleElementTree.remove(Element(10, 10)));
  EXPECT_EQ(singleElementTree.getSize(), 0);
  EXPECT_EQ(singleElementTree.findElement(Element(10, 10)), nullptr);
}
TEST_F(BSTreeTest, RemoveRootWithLeftChild) {
  BSTree twoElementTree;
  twoElementTree.insert(Element(10, 10));
  twoElementTree.insert(Element(1, 1));
  EXPECT_TRUE(twoElementTree.remove(Element(10, 10)));
  EXPECT_EQ(twoElementTree.getSize(), 1);
  EXPECT_EQ(twoElementTree.findElement(Element(10, 10)), nullptr);
}
TEST_F(BSTreeTest, RemoveRootWithRightChild) {
  BSTree twoElementTree;
  twoElementTree.insert(Element(10, 10));
  twoElementTree.insert(Element(11, 11));
  EXPECT_TRUE(twoElementTree.remove(Element(10, 10)));
  EXPECT_EQ(twoElementTree.getSize(), 1);
  EXPECT_EQ(twoElementTree.findElement(Element(10, 10)), nullptr);
}
TEST_F(BSTreeTest, RemoveNodeWithOneChild) {
  getTree()->insert(Element(1, 1));
  EXPECT_TRUE(getTree()->remove(Element(5, 5)));
  EXPECT_EQ(getTree()->getSize(), 3);
  EXPECT_EQ(getTree()->findElement(Element(5, 5)), nullptr);
}
TEST_F(BSTreeTest, FindAll) {
  const auto tree = getTree();
  const auto elements = tree->getAllElements();
  ASSERT_EQ(elements.size(), 3);
  EXPECT_EQ(elements[0], Element(5, 5));
  EXPECT_EQ(elements[1], Element(10, 10));
  EXPECT_EQ(elements[2], Element(15, 15));
}