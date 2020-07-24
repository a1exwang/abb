#include <vector>
#include <tuple>
#include <iostream>


// s2 = s1+l1
// merge [s1, s1+l1) and [s2,s2+l2) into output[so:so+l1+l2)
void merge(std::vector<int> &output, int so, const std::vector<int> &arr, int s1, int l1, int s2, int l2) {
  int i1 = s1;
  int i2 = s2;
  while (true) {
    if (i1 == s1+l1) {
      while (i2 < s2+l2) {
        output[so++] = arr[i2++];
      }
      return;
    } else if (i2 == s2+l2) {
      while (i1 < s1+l1) {
        output[so++] = arr[i1++];
      }
      return;
    } else {
      if (arr[i1] <= arr[i2]) {
        output[so++] = arr[i1++];
      } else {
        output[so++] = arr[i2++];
      }
    }
  }
}

// 2 4 3 1 5
// 2 4 1 3 5
void mergesort(std::vector<int> &arr) {
  std::vector<int> output(arr.size());
  int width = 1;
  do {
    // make sure every "width" elements are sorted
    auto half_width = width;
    width <<= 1;
    for (int i = 0; i < arr.size(); i += width) {
      if (i + half_width < arr.size()) {
        auto second_width = std::min<int>(arr.size(), i+width) - (i+half_width);
        merge(output, i, arr, i, half_width, i+half_width, second_width);
      } else {
        std::copy(arr.begin() + i, arr.end(), output.begin() + i);
      }
    }
    // after these merges, the maximum sorted size is width
    arr.swap(output);
  } while (width < arr.size());
}

int main() {
  std::vector<std::tuple<std::vector<int>, std::vector<int>>> test_cases = {
      {{}, {}},
      {{1}, {1}},
      {{2, 1}, {1, 2}},
      {{3,2,1}, {1,2,3}},
      {{4,5,6,1,2,3}, {1,2,3,4,5,6}},
      {{3,3,3,1,1,2},{1,1,2,3,3,3}},
  };
  for (auto &[input, expected] : test_cases) {
    auto output = input;
    mergesort(output);
    if (output != expected) {
      std::cerr << "Error: " << std::endl;
      std::cerr << "For input: '";
      for (auto i : input) {
        std::cerr << i << " ";
      }
      std::cerr << std::endl;
      std::cerr << "The output should be: '";
      for (auto i : expected) {
        std::cerr << i << " ";
      }
      std::cerr << std::endl;
      std::cerr << "But the actual output is: '";
      for (auto i : output) {
        std::cerr << i << " ";
      }
      std::cerr << std::endl;
      return 1;
    }
  }
  std::cout << "All tests have passed" << std::endl;
}