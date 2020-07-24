#include <iostream>
#include <vector>

template <typename T>
struct BinaryHeap {
  void push(T value) {
    data.emplace_back(std::move(value));
    bottom_up(data.size() - 1);
  }
  T pop() {
    auto ret = std::move(data.front());
    std::swap(data.back(), data.front());
    data.pop_back();
    top_down(0);
    return ret;
  }
  const T &top() const {
    return data.front();
  }

  size_t size() const {
    return data.size();
  }

 private:
  int left(int i) const {
    return 2*i+1;
  }
  int right(int i) {
    return 2*i+2;
  }
  int parent(int i) {
    return (i-1)/2;
  }
  void bottom_up(int index) {
    if (index != 0) {
      auto p = parent(index);
      if (data[index] < data[p]) {
        std::swap(data[index], data[p]);
        bottom_up(p);
      }
    }
  }
  void top_down(int top_index) {
    auto l = left(top_index);
    auto r = right(top_index);
    if (l < data.size() && r < data.size()) {
      if (data[top_index] <= data[l] && data[top_index] <= data[r]) {
        // done
      } else {
        if (data[l] <= data[r]) {
          std::swap(data[l], data[top_index]);
          top_down(l);
        } else {
          std::swap(data[r], data[top_index]);
          top_down(r);
        }
      }
    } else if (l < data.size()) {
      if (data[l] <= data[top_index]) {
        std::swap(data[l], data[top_index]);
        top_down(l);
      }
    }
  }

  std::vector<T> data;
};


int main() {
  BinaryHeap<int> heap;

  std::vector<int> arr = {3, 5, 2, 4};
  for (auto a : arr) {
    heap.push(a);
  }
  while (heap.size() != 0) {
    auto value = heap.pop();
    std::cout << value << std::endl;
  }
}