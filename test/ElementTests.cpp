#include "../src/Element.hpp"
#include <gtest/gtest.h>

TEST(ElementTests, DefaultConstructor) {
  const Element e;
  EXPECT_EQ(e.getKey(), -1);
  EXPECT_EQ(e.getValue(), -1);
}

TEST(ElementTests, ParameterizedConstructor) {
  const Element e(10, 20);
  EXPECT_EQ(e.getKey(), 10);
  EXPECT_EQ(e.getValue(), 20);
}

TEST(ElementTests, SetValue) {
  Element e(10, 20);
  e.setValue(30);
  EXPECT_EQ(e.getValue(), 30);
}

TEST(ElementTests, EqualityOperator) {
  const Element e1(20, 20);
  const Element e2(20, 20);
  EXPECT_TRUE(e1 == e2);
  const Element e3(10, 30);
  EXPECT_FALSE(e1 == e3);
}

TEST(ElementTests, ThreeWayComparison) {
  const Element e1(20, 20);
  const Element e2(10, 30);
  const Element e3(20, 20);
  EXPECT_TRUE(e1 > e2);
  EXPECT_TRUE(e3 >= e1);
  EXPECT_TRUE(e1 == e3);
}

TEST(ElementTests, CheckKeyWithElement) {
  const Element e1(10, 20);
  const Element e2(10, 30);
  const Element e3(15, 20);
  EXPECT_TRUE(e1.checkKey(e2));
  EXPECT_FALSE(e1.checkKey(e3));
}

TEST(ElementTests, CheckKeyWithInt) {
  const Element e(10, 20);
  EXPECT_TRUE(e.checkKey(10));
  EXPECT_FALSE(e.checkKey(15));
}

TEST(ElementTests, ToString) {
  const Element e(10, 20);
  EXPECT_EQ(e.toString(), "(20;10)");
}

TEST(ElementTests, StreamOperator) {
  const Element e(10, 20);
  std::ostringstream os;
  os << e;
  EXPECT_EQ(os.str(), "key: 10 value: 20");
}