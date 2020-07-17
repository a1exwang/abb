#include <cassert>

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

// sort [start, end)
template <typename T>
void quicksort(std::vector<T> &arr, size_t start, size_t end) {
  // len <= 1
  if (start + 1 >= end) {
    return;
  }

  // len >= 2
  auto pivot = arr[start];
  // [l, r) >= 1
  size_t l = start+1, r = end;

  while (l+1 < r) {
    if (arr[l] < pivot) {
      l++;
    } else {
      r--;
      std::swap(arr[l], arr[r]);
    }
  }

  size_t pivot_index = 0;
  if (arr[l] <= pivot) {
    std::swap(arr[start], arr[l]);
    pivot_index = l;
  } else {
    // if l-1 == start, this is the worst case: pivot_index == start
    std::swap(arr[start], arr[l-1]);
    pivot_index = l-1;
  }

  quicksort(arr, start, pivot_index);
  quicksort(arr, pivot_index+1, end);
}

template <typename T>
void quicksort(std::vector<T> &arr) {
  quicksort(arr, 0, arr.size());
}

int main() {
  size_t length = 1000000;
  std::vector<int> a(length);
  std::mt19937 rng;
  std::uniform_int_distribution<int> dist;
  std::generate(a.begin(), a.end(), [&]() { return dist(rng); });
  auto a1 = a;
  auto a2 = a;
  auto t0 = std::chrono::high_resolution_clock::now();
  std::sort(a1.begin(), a1.end());
  auto t1 = std::chrono::high_resolution_clock::now();
  quicksort(a2);
  auto t2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < a1.size(); i++) {
    if (a1[i] != a2[i]) {
      std::cerr << "result not matched " << std::endl;
      return 1;
    }
  }
  std::cout << "all tests have passed" << std::endl;
  std::cout << "std::sort: " << std::chrono::duration<double, std::milli>(t1-t0).count() << "ms, "
            << "quicksort: " << std::chrono::duration<double, std::milli>(t2-t1).count() << std::endl;
}