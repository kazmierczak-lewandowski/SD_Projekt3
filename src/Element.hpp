#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <format>
#include <ostream>

class Element {
 private:
  int key;
  int value;

 public:
  Element(const int key, const int value) : key(key), value(value) {}
  friend std::ostream &operator<<(std::ostream &os, const Element &obj) {
    return os << "key: " << obj.key << " value: " << obj.value;
  }
  Element() : key(-1), value(-1) {}
  auto operator<=>(const Element &other) const { return key <=> other.key; }
  bool operator==(const Element &other) const { return value == other.value && key == other.key; }
  void setValue(const int newValue) { this->value = newValue; }
  [[nodiscard]] int getKey() const { return key; }
  [[nodiscard]] int getValue() const { return value; }
  [[nodiscard]] bool checkKey(const Element &other) const {
    return key == other.key;
  }
  [[nodiscard]] bool checkKey(const int otherKey) const {
    return key == otherKey;
  }
  [[nodiscard]] std::string toString() const {
    return std::format("({};{})", value, key);
  }
};

#endif  // ELEMENT_HPP
