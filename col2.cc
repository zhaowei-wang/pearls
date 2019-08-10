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
// 3. Given a dictionary of words, find all sets of anagrams.


int main(int argc, char** argv) {
  auto find_missing_integer = FindMissingInteger();
  find_missing_integer.Run();
  return 0;
}
