#include "Analysis.hpp"

#include <curses.h>

#include <chrono>
#include <format>
#include <fstream>
#include <map>
#include <string>

#include "Element.hpp"
#include "HashMap.hpp"

void Analysis::printSubTest(const int size, const int iteration) {
  move(1, 0);
  clrtoeol();
  mvprintw(1, 0, "%s",
           std::format("{} test for {}\n", iteration, size).c_str());
  refresh();
}
void Analysis::printTestHeader(const BucketType type, std::string title) {
  using enum BucketType;
  std::string typeString;
  switch (type) {
    case AVL: {
      typeString = "AVL";
      break;
    }
    case BST: {
      typeString = "BST";
      break;
    }
    case DLL: {
      typeString = "DLL";
      break;
    }
  }
  const auto string = std::format("Analyzing {} of {}", title, typeString);
  mvprintw(0, 0, "%s", string.c_str());
}
void Analysis::writeToFile(const std::string &filename,
                           const std::map<int, long> &data) {
  std::ofstream ofs("results/" + filename);
  ofs << "size;time" << std::endl;
  for (const auto &[key, value] : data) {
    ofs << key << ";" << value << std::endl;
  }
  ofs.close();
}
void Analysis::prepareToTest(const int size, const int iteration,
                             HashMap &map) {
  printSubTest(size, iteration);
  HashMap::fillFromFile(map, "numbers.txt", size);
}
std::map<int, long> Analysis::analyzeInsert(const BucketType bucketType) {
  clear();
  std::map<int, long> result;
  printTestHeader(bucketType, "Insert");
  for (int i = 100'000; i <= 3'000'000; i += 100'000) {
    long average = 0;
    for (int j = 0; j < ITERATIONS; j++) {
      HashMap map(bucketType);
      prepareToTest(i, j, map);
      const auto start = std::chrono::high_resolution_clock::now();
      map.insert({5'000'000, 5'000'000});
      const auto end = std::chrono::high_resolution_clock::now();
      average +=
          std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
              .count();
    }
    result.insert(std::pair(i, average / ITERATIONS));
  }
  return result;
}
std::map<int, long> Analysis::analyzeRemove(const BucketType bucketType) {
  clear();
  std::map<int, long> result;
  printTestHeader(bucketType, "Remove");
  for (int i = 100'000; i <= 3'000'000; i += 100'000) {
    long average = 0;
    for (int j = 0; j < ITERATIONS; j++) {
      HashMap map(bucketType);
      prepareToTest(i, j, map);
      const Element randElement = map.getRandomElement();
      const auto start = std::chrono::high_resolution_clock::now();
      map.remove(randElement);
      const auto end = std::chrono::high_resolution_clock::now();
      average +=
          std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
              .count();
    }
    result.insert(std::pair(i, average / ITERATIONS));
  }
  return result;
}
void Analysis::analysis() {
  using enum BucketType;
  std::map<int, long> data;
  data = analyzeInsert(BST);
  writeToFile("InsertionBST.csv", data);
  data = analyzeRemove(BST);
  writeToFile("RemoveBST.csv", data);

  data = analyzeInsert(AVL);
  writeToFile("InsertionAVL.csv", data);
  data = analyzeRemove(AVL);
  writeToFile("RemoveAVL.csv", data);

  data = analyzeInsert(DLL);
  writeToFile("InsertionDLL.csv", data);
  data = analyzeRemove(DLL);
  writeToFile("RemoveDLL.csv", data);
}