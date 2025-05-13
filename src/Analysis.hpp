#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP
#include <map>
#include <string>

#include "HashMap.hpp"
class Analysis {
 private:
  static constexpr int ITERATIONS = 10;
  static void printSubTest(int size, int iteration);
  static void printTestHeader(BucketType type, std::string title);
  static void writeToFile(const std::string& filename,
                          const std::map<int, long>& data);
  static void prepareToTest(int size, int iteration, HashMap& map);
  static std::map<int, long> analyzeInsert(BucketType bucketType);
  static std::map<int, long> analyzeRemove(BucketType bucketType);
 public:
  static void analysis();
};

#endif  // ANALYSIS_HPP
