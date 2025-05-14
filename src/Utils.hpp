#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <random>

#include "Element.hpp"

class Utils {
 public:
  static int rng(int min, int max);
  static int gauss(int min, int max);
  struct TreeNode {
    Element element;
    std::unique_ptr<TreeNode> left = nullptr;
    std::unique_ptr<TreeNode> right = nullptr;
    TreeNode *parent = nullptr;
    int height = 0;
    explicit TreeNode(Element const e) : element(e) {}
  };

 private:
  static inline std::mt19937 gen{std::random_device{}()};
};

#endif  // UTILS_HPP