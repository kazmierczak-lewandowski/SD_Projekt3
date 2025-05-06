#include <gtest/gtest.h>
#include "../src/Avl.hpp"
#include "../src/Element.hpp"
bool isCorrect(const AVLTree::AVLNode *node) { // NOLINT(*-no-recursion)
  if (node == nullptr) return true;
  if (node->left) {
    if (node->left->element > node->element || node->left->parent != node) return false;
  }
  if (node->right) {
    if (node->right->element < node->element || node->right->parent != node) return false;
  }
  return isCorrect(node->left.get()) && isCorrect(node->right.get());
}

bool isBalanced(const AVLTree::AVLNode *node) { // NOLINT(*-no-recursion)
  if (node == nullptr) return true;

  const int leftHeight = node->left ? node->left->height : -1;
  const int rightHeight = node->right ? node->right->height : -1;

  if (std::abs(leftHeight - rightHeight) > 1) return false;

  return isBalanced(node->left.get()) && isBalanced(node->right.get());
}

class AvlTest : public testing::Test {
 private:
  AVLTree tree;

 protected:
  void SetUp() override {
    tree.insert(Element{1, 10});
    tree.insert(Element{2, 20});
    tree.insert(Element{3, 30});
    tree.insert(Element{4, 40});
  }
  AVLTree* getTree() { return &tree; }
};

TEST_F(AvlTest, InsertElementIntoEmptyTree) {
  AVLTree emptyTree;
  EXPECT_TRUE(emptyTree.isEmpty());

  emptyTree.insert(Element{5, 50});

  EXPECT_EQ(emptyTree.getSize(), 1);
  EXPECT_FALSE(emptyTree.isEmpty());

  const auto root = emptyTree.getRoot();
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->element, Element(5, 50));
}

TEST_F(AvlTest, InsertMaintainsBalance) {
  const auto tree = getTree();
  tree->insert(Element{5, 50});

  EXPECT_EQ(tree->getSize(), 5);
  EXPECT_TRUE(isBalanced(tree->getRoot()));
}

TEST_F(AvlTest, RemoveElementMaintainsBalance) {
  const auto tree = getTree();
  tree->remove(Element{2, 20});

  EXPECT_EQ(tree->getSize(), 3);
  EXPECT_TRUE(isBalanced(tree->getRoot()));
}

TEST_F(AvlTest, FindExistingElement) {
  const auto tree = getTree();
  const auto node = tree->findElement(Element{3, 30});

  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->element, Element(3, 30));
}

TEST_F(AvlTest, FindNonExistentElement) {
  const auto tree = getTree();
  const auto node = tree->findElement(Element{99, 999});

  EXPECT_EQ(node, nullptr);
}

TEST_F(AvlTest, RemoveAllElements) {
  const auto tree = getTree();
  EXPECT_TRUE(tree->remove(Element{1, 10}));
  EXPECT_TRUE(tree->remove(Element{2, 20}));
  EXPECT_TRUE(tree->remove(Element{3, 30}));
  EXPECT_TRUE(tree->remove(Element{4, 40}));

  EXPECT_EQ(tree->getSize(), 0);
  EXPECT_TRUE(tree->isEmpty());
}

TEST_F(AvlTest, FindAndReplaceExistingElement) {
  const auto tree = getTree();
  const Element newElement{3, 300};
  EXPECT_TRUE(tree->findAndReplace(newElement));

  const auto node = tree->findElement(newElement);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->element.getValue(), 300);
}

TEST_F(AvlTest, FindAndReplaceNonExistentElement) {
  const auto tree = getTree();
  const Element nonExistent{99, 999};
  EXPECT_FALSE(tree->findAndReplace(nonExistent));
  EXPECT_EQ(tree->getSize(), 4);
}