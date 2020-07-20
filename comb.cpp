#include <chrono>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

class Combination {
 public:
  Combination(int n) : n(n), resultByCount(n+1) {
    calculate();
  }

  void print() {
    for (int i = 0; i <= n; i++) {
      std::cout << i << ": " << std::endl;
      for (const auto &comb : resultByCount[i]) {
        for (auto num : comb) {
          std::cout << num << " ";
        }
        std::cout << std::endl;
      }
      std::cout << "----------" << std::endl;
    }
  }

 private:
  void calculate() {
    for (int i = 0; i <= n; i++) {
      calculate(i);
    }
  }

  // generate all combinations of numbers in [0, n)
  void calculate(int count) {
    if (count == 0) {
      resultByCount[count].emplace_back();
    } else {
      auto &lastResults = resultByCount[count-1];
      for (const std::vector<int> &lastResult : lastResults) {
        int startIndex = 0;
        if (lastResult.empty()) {
          startIndex = 0;
        } else {
          startIndex = lastResult.back() + 1;
        }
        for (int j = startIndex; j < n; j++) {
          auto &newResult = resultByCount[count].emplace_back(lastResult);
          newResult.push_back(j);
        }
      }
    }
  }

 public:
  int n;
  std::vector<std::vector<std::vector<int>>> resultByCount;
};

class Arrangement {
 public:
  Arrangement(int n) : n(n), resultByCount(n+1) {
    for (int i = 0; i < n; i++) {
      all.push_back(i);
    }
    calculate();
  }

  void print() {
    for (int i = 0; i <= n; i++) {
      std::cout << i << ": " << std::endl;
      for (const auto &comb : resultByCount[i]) {
        for (auto num : comb) {
          std::cout << num << " ";
        }
        std::cout << std::endl;
      }
      std::cout << "----------" << std::endl;
    }
  }

 private:
  void calculate() {
    for (int i = 0; i <= n; i++) {
      calculate(i);
    }
  }

  // generate all combinations of numbers in [0, n)
  void calculate(int count) {
    if (count == 0) {
      resultByCount[count].emplace_back();
    } else {
      // T(n) = T(n-1) * n
      // T(n) = O(n!)
      auto &lastResults = resultByCount[count-1];
      for (const std::vector<int> &lastResult : lastResults) {
        for (auto pivot : complement(lastResult)) {
          auto &newResult = resultByCount[count].emplace_back(lastResult);
          newResult.push_back(pivot);
        }
      }
    }
  }

  // O(n)
  std::vector<int> complement(std::vector<int> nums) const {
    std::vector<bool> found(n, false);
    for (auto n : nums) {
      found[n] = true;
    }
    std::vector<int> result;
    for (int i = 0; i < n; i++) {
      if (!found[i]) {
        result.push_back(i);
      }
    }
    return result;
  }

 public:
  int n;
  std::vector<int> all;
  std::vector<std::vector<std::vector<int>>> resultByCount;
};


// calculate arrangement or combination of N numbers
int main() {
  int n = 15;
  int m = 7;
  auto t0 = std::chrono::high_resolution_clock::now();
  // O(2^n)
  Combination combination(n);
  auto t1 = std::chrono::high_resolution_clock::now();
//  combination.print();
  std::cout << "combination " << n << ": " << std::chrono::duration<double, std::milli>(t1 - t0).count() << "ms" << std::endl;

  auto t2 = std::chrono::high_resolution_clock::now();
  // O(m!)
  Arrangement arrangement(m);
  auto t3 = std::chrono::high_resolution_clock::now();
//  arrangement.print();
  std::cout << "arrangement " << m << ": " << std::chrono::duration<double, std::milli>(t3 - t2).count() << "ms" << std::endl;
}