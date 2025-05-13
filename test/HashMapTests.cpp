#include <gtest/gtest.h>

#include "Element.hpp"
#include "HashMap.hpp"
class HashMapTest : public testing::TestWithParam<BucketType> {
 private:
  HashMap hashMap{GetParam()};

 protected:
  HashMap* getMap() { return &hashMap; }
};

INSTANTIATE_TEST_SUITE_P(AllBucketTypes, HashMapTest,
                         ::testing::Values(BucketType::AVL, BucketType::BST,
                                           BucketType::DLL));
TEST_P(HashMapTest, AddMaxKey) {
  constexpr int key = 5'000'000;
  constexpr int value = 1;
  const Element e(key, value);
  getMap()->insert(e);
}
TEST_P(HashMapTest, InsertAndRemove) {
  const Element e1(1, 100);
  getMap()->insert(e1);
  EXPECT_TRUE(getMap()->remove(e1));
  EXPECT_FALSE(getMap()->remove(e1));
}

TEST_P(HashMapTest, InsertDuplicate) {
  const Element e1(1, 100);
  const Element e2(1, 200);
  constexpr int bucket = ((1'234'567 * 1 + 987'654) % 5'000'003) % 10'000;
  getMap()->insert(e1);
  getMap()->insert(e2);
  EXPECT_EQ(getMap()->getBucketSize(bucket), 1);
}
TEST_P(HashMapTest, FillFromFileInsertsCorrectElements) {
  const std::string filename = "test_elements.txt";
  std::ofstream ofs(filename);
  ofs << "0 0\n1 1\n2 2\n";
  ofs.close();
  HashMap::fillFromFile(*getMap(), filename, 3);
  constexpr int bucket1 = ((1'234'567 * 0 + 987'654) % 5'000'003) % 10'000;
  constexpr int bucket2 = ((1'234'567 * 1 + 987'654) % 5'000'003) % 10'000;
  constexpr int bucket3 = ((1'234'567 * 2 + 987'654) % 5'000'003) % 10'000;
  EXPECT_EQ(getMap()->getBucketSize(bucket1), 1);
  EXPECT_EQ(getMap()->getBucketSize(bucket2), 1);
  EXPECT_EQ(getMap()->getBucketSize(bucket3), 1);

  std::remove(filename.c_str());
}