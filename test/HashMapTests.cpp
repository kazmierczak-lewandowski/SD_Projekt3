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

TEST_P(HashMapTest, InsertAndRemove) {
  const auto map = getMap();
  const Element e1(1, 100);
  map->insert(e1);
  EXPECT_TRUE(map->remove(e1));
  EXPECT_FALSE(map->remove(e1));
}
TEST_P(HashMapTest, AddMaxKey) {
  constexpr int key = 5'000'000;
  constexpr int value = 1;
  const Element e(key, value);
  getMap()->insert(e);
}
TEST_P(HashMapTest, InsertDuplicate) {
  const auto map = getMap();
  const Element e1(1, 100);
  const Element e2(1, 200);
  constexpr int bucket = ((1'234'567 * 1 + 987'654) % 5'000'003) % 10'000;
  map->insert(e1);
  map->insert(e2);
  EXPECT_EQ(map->getBucketSize(bucket), 1);
}
TEST_P(HashMapTest, FillFromFileInsertsCorrectElements) {
  auto map = getMap();
  const std::string filename = "test_elements.txt";
  std::ofstream ofs(filename);
  ofs << "0 0\n1 1\n2 2\n";
  ofs.close();
  HashMap::fillFromFile(*map, filename, 3);
  constexpr int bucket1 = ((1'234'567 * 0 + 987'654) % 5'000'003) % 10'000;
  constexpr int bucket2 = ((1'234'567 * 1 + 987'654) % 5'000'003) % 10'000;
  constexpr int bucket3 = ((1'234'567 * 2 + 987'654) % 5'000'003) % 10'000;
  EXPECT_EQ(map->getBucketSize(bucket1), 1);
  EXPECT_EQ(map->getBucketSize(bucket2), 1);
  EXPECT_EQ(map->getBucketSize(bucket3), 1);

  std::remove(filename.c_str());
}
TEST_P(HashMapTest, GetRandomElement) {
  const auto map = getMap();
  const Element e1(1, 100);
  const Element e2(1, 200);
  map->insert(e1);
  map->insert(e2);
  const auto element = map->getRandomElement();
  EXPECT_TRUE(map->remove(element));
}