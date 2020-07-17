#include <cassert>

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

template <typename T>
void quicksort_simple(std::vector<T> &arr, size_t start, size_t end) {
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
size_t median(std::vector<T> &arr, size_t a, size_t b, size_t c) {
  if (arr[a] > arr[b] && arr[a] > arr[c]) {
    if (arr[b] < arr[c]) {
      return c;
    } else {
      return b;
    }
  } else if (arr[b] > arr[c] && arr[b] > arr[a]) {
    if (arr[a] < arr[c]) {
      return c;
    } else {
      return a;
    }
  } else {
    if (arr[a] < arr[b]) {
      return b;
    } else {
      return a;
    }
  }
}

// sort [start, end)
template <typename T>
void quicksort_loop(std::vector<T> &arr, size_t start, size_t end) {
  while (true) {
    // len <= 1
    if (start + 1 >= end) {
      return;
    }

    // len >= 2

    // choose a median number as pivot to prevent worst case
    auto mid = median(arr, start, (start+end)/2, end-1);
    std::swap(arr[start], arr[mid]);

    auto pivot = arr[start];
    // [l, r) >= 1
    size_t l = start+1, r = end;

    while (l+1 < r) {
      while (l+1 < r && arr[l] <= pivot) {
        l++;
      }
      while (l+1 < r && arr[r-1] >= pivot) {
        r--;
      }
      std::swap(arr[l], arr[r-1]);
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

    // always recur the shorter first
    if (pivot_index - start < end - (pivot_index+1)) {
      quicksort_loop(arr, start, pivot_index);

//      quicksort(arr, pivot_index+1, end);
      start = pivot_index+1;
    } else {
      quicksort_loop(arr, pivot_index+1, end);

//      quicksort(arr, start, pivot_index);
      end = pivot_index;
    }
  }
}

template <typename T>
void quicksort(std::vector<T> &arr) {
  quicksort_loop(arr, 0, arr.size());
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