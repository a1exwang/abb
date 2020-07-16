#include <iostream>
#include <algorithm>
#include <cassert>


template <typename T>
class StreamMedian {
 public:
  StreamMedian() {}
  void push_back(T t) {
    if (big_values_.empty() || t >= big_values_.front()) {
      push_heap_big(t);
    } else if (small_values_.empty() || t <= small_values_.front()) {
      push_heap_small(t);
    } else /*if (small_values_.back() < t && t < big_values_.back())*/ {
      push_heap_big(t);
    }
    balance();
  }
  T get_median() const {
    if (big_values_.size() == small_values_.size()) {
      if (big_values_.empty()) {
        return 0;
      } else {
        //std::cout << "median " << big_values_.front() << " " << small_values_.front() << std::endl;
        return (big_values_.front() + small_values_.front()) / 2;
      }
    } else {
      assert(big_values_.size() == small_values_.size() + 1);
      //std::cout << "median " << big_values_.front() << std::endl;
      return big_values_.front();
    }
  }
 private:
  struct ReverseCompare {
    bool operator()(const T& lhs, const T& rhs) {
      return lhs > rhs;
    }
  };
  constexpr static ReverseCompare reverse_compare_{};
  void print() {
    std::cout << "small: ";
    for (auto small : small_values_) {
      std::cout << small << " ";
    }
    std::cout << std::endl;
    std::cout << "big: ";
    for (auto big : big_values_) {
      std::cout << big << " ";
    }
    std::cout << std::endl << std::endl;
  }
 private:
  void push_heap_big(T value) {
//    std::cout << "push big " << value << std::endl;
    big_values_.push_back(value);
    std::push_heap(big_values_.begin(), big_values_.end(), reverse_compare_);
  }
  T pop_heap_big() {
    std::pop_heap(big_values_.begin(), big_values_.end(), reverse_compare_);
    auto ret = big_values_.back();
//    std::cout << "pop big " << ret << std::endl;
    big_values_.pop_back();
    return ret;
  }
  void push_heap_small(T value) {
//    std::cout << "push small " << value << std::endl;
    small_values_.push_back(value);
    std::push_heap(small_values_.begin(), small_values_.end());
  }
  T pop_heap_small() {
    std::pop_heap(small_values_.begin(), small_values_.end());
    auto ret = small_values_.back();
//    std::cout << "pop small " << ret << std::endl;
    small_values_.pop_back();
    return ret;
  }
  void balance() {
    while (small_values_.size() > big_values_.size()) {
      auto popped = pop_heap_small();
      push_heap_big(popped);
    }
    while (small_values_.size() + 1 < big_values_.size()) {
      auto popped = pop_heap_big();
      push_heap_small(popped);
    }
  }
  // small_values_.size() == big_values_.size() || big_values_.size() == small_values.size() + 1
  std::vector<T> small_values_;
  std::vector<T> big_values_;
};

template <typename It>
int get_median(It begin, It end) {
  auto n = std::distance(begin, end);
  if (n == 0) {
    return 0;
  } else if (n % 2 == 0) {
    std::nth_element(begin, begin+n/2, end);
    std::nth_element(begin, begin+n/2-1, end);
    return (*(begin+n/2) + *(begin + n/2-1)) / 2;
  } else {
    std::nth_element(begin, begin+n/2, end);
    return *(begin+n/2);
  }
}

int main() {
  std::vector<int> stream = {6,10,2,6,5};
  StreamMedian<int> stream_median;
  for (auto it = stream.begin(); it != stream.end(); it++) {
    stream_median.push_back(*it);
    auto median = stream_median.get_median();
    auto expected = get_median(stream.begin(), it+1);
    if (median != expected) {
      std::cerr << "Wrong answer " << median << " != " << expected << std::endl;
      abort();
    }
  }
  std::cout << "All tests have passed" << std::endl;
}