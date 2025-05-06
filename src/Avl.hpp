#ifndef AVLTree_HPP
#define AVLTree_HPP
#include <memory>

#include "Collection.hpp"

#include <queue>

class AVLTree final : public Collection {

public:
  struct AVLNode{
    Element element;
    std::unique_ptr<AVLNode> left = nullptr;
    std::unique_ptr<AVLNode> right = nullptr;
    AVLNode *parent = nullptr;
    int height = 0;
    explicit AVLNode(Element const e) : element(e){}
  };
  explicit AVLTree() = default;
  ~AVLTree() override = default;
  void insert(Element element) override;
  [[nodiscard]] AVLNode* findElement(const Element &element) const;
  [[nodiscard]] AVLNode* getRoot() const {
    return root.get();
  }
  bool remove(Element element) override;
private:
  std::unique_ptr<AVLNode> root = nullptr;
  void LLRotation(std::unique_ptr<AVLNode> &current);
  void RRRotation(std::unique_ptr<AVLNode> &current);
  void LRRotation(std::unique_ptr<AVLNode> &current);
  void RLRotation(std::unique_ptr<AVLNode> &current);
  static int checkBalance(const AVLNode *current);
  void balance(std::unique_ptr<AVLNode> &current);
  static void updateHeight(AVLNode *node);
  void updateBalanceUp(AVLNode *node);
  void deleteNode(AVLNode *node);
  bool findAndReplace(Element element) override;
};

#endif // AVLTree_HPP
