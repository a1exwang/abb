#include <string>
#include <iostream>
#include <tuple>
#include <vector>

int kmp_search(const std::string &s, const std::string &pattern) {
  // partial match table
  std::vector<int> pmt(pattern.size(), 0);
  for (int i = 1, j = 0; i < pattern.size(); i++) {
    if (pattern[i] == pattern[j]) {
      j++;
    } else {
      j = 0;
    }
    pmt[i] = j;
  }

  // si is index of s
  // pj is index of pattern
  int si = 0, pj = 0;
  while (si < s.size() && pj < pattern.size()) {
    if (s[si] == pattern[pj]) {
      // matched, continue search
      si++;
      pj++;
    } else {
      if (pj == 0) {
        // not matched, and s[si] != pattern[0], move forward s
        si++;
      } else {
        // not matched, but we can use PMT
        pj = pmt[pj-1];
      }
    }
  }

  if (pj == pattern.size()) {
    return si - pattern.size();
  } else {
    return s.size();
  }
}

int main() {
  std::vector<std::tuple<std::string, std::string, int>> test_cases = {
      {"", "a", 0},
      {"", "", 0},
      {"abcd", "", 0},
      {"abc", "a", 0},
      {"dabc", "abc", 1},
      {"abcabcccabcdabb", "abcdab", 8},
      {"aabaabcabcabdaaabe", "abcabcabdaaab", 4},
  };
  for (auto &[s, pattern, result] : test_cases) {
    auto index = kmp_search(s, pattern);
    if (index != result) {
      std::cerr << "test failure for '" << s << "', p='" << pattern << "'" << std::endl;
      std::cerr << "expected=" << result << ", actual=" << index << std::endl;
      return 1;
    }
  }
  std::cout << "all tests have passed" << std::endl;
  return 0;
}