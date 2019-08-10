#include <algorithm>
#include <assert.h>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <unordered_set>

template <class T>
void ShuffleVector(std::vector<T>* vector) {
  assert(vector != nullptr);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(vector->begin(), vector->end(), g);
}

// 1. Given at most four billion integers in random order, find an integer not in
// the list.
class FindMissingInteger {
 public:
  FindMissingInteger() {
    auto integers = std::vector<int>(kMaxInputSize);
    std::iota(integers.begin(), integers.end(), -10);
    ShuffleVector(&integers);
    for (int i = 0; i < integers.size(); ++i) {
      if (missing_indices_.find(i) != missing_indices_.end()) {
        continue;
      }
      input_.push_back(integers.at(i));
    }

    printf("FindMissingInteger: Input vector:\n");
    for (auto value : input_) {
      printf("%d ", value);
    }
    printf("\n");
  }

  void Run() {
    std::sort(input_.begin(), input_.end());

    int result = INT32_MIN;
    int i = 0;
    int j = input_.size() - 1;

    while (i <= j) {
      const int mid = (i + j) / 2;
      if (Check(input_, mid + 1, j)) {
        i = mid + 1;
      } else if (Check(input_, i, mid - 1)) {
        j = mid - 1;
      } else {
        if (Check(input_, mid - 1, mid)) {
          result = input_.at(mid) - 1;
        } else {
          result = input_.at(mid) + 1;
        }
        break;
      }
    }

    printf("Result: %d\n", result);
  }

 private:
  static constexpr int kMaxInputSize = 10;
  const std::unordered_set<int> missing_indices_ = {2, 5};
  std::vector<int> input_;

  bool Check(const std::vector<int>& vec, int i, int j) {
    if (i > j) return false;
    return vec.at(j) - vec.at(i) != j - i;
  }
};

// 2. Rotate a one-dimensional vector of N elements left by i positions. Can you
// rotate the vector in time proprotional to N using only a few dozen extra bytes
// of storage?
class RotateVector {
 public:
  RotateVector() {
    input_ = std::vector<int>(10);
    std::iota(input_.begin(), input_.end(), 0);
  }

  void Run() {
    for (int value : input_) printf("%d ", value);
    printf("\n");
    Rotate(&input_, 3);
    for (int value : input_) printf("%d ", value);
    printf("\n");
  }

 private:
  std::vector<int> input_;

  void Rotate(std::vector<int>* vec, int rotate_num) {
    assert(vec != nullptr);
    rotate_num = rotate_num % vec->size();
    FlipBackwards(vec, 0, rotate_num - 1);
    FlipBackwards(vec, rotate_num, vec->size() - 1);
    FlipBackwards(vec, 0, vec->size() - 1);
  }

  void FlipBackwards(std::vector<int>* vec, int i, int j) {
    assert(i <= j && i >= 0 && j < vec->size());
    for (int k = 0; k < (j - i) / 2; ++k) {
      Swap(&vec->at(i + k), &vec->at(j - k));
    }
  }

  void Swap(int* a, int* b) {
    assert (a != nullptr && b != nullptr);
    int temp = *a;
    *a = *b;
    *b = temp;
  }
};

int main(int argc, char** argv) {
  printf("--1--\n");
  auto find_missing_integer = FindMissingInteger();
  find_missing_integer.Run();

  printf("--2--\n");
  auto rotate_vector = RotateVector();
  rotate_vector.Run();
  return 0;
}
