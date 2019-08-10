#include <iostream>
#include <vector>

class BinarySearch {
 public:
  int Find(const std::vector<int>& vec, int value) {
    int result = -1;

    // Invariant is i <= j, and value is in vec[i], ..., vec[j].
    int i = 0;
    int j = vec.size() - 1;
    while (i <= j) {
      int mid = (j + i) / 2;
      int mid_value = vec.at(mid);
      // Enforces value is in vec[i], ..., vec[j].
      if (mid_value < value) {
        i = mid + 1;
      } else if (mid_value > value) {
        j = mid - 1;
      } else {
        result = mid;
        break;
      }
    }
    return result;
  }

  int FindFirstOccurence(const std::vector<int>& vec, int value) {
    int result = -1;

    // Invariant is i <= j, value is in vec[i], ..., vec[j], and k for
    // which vec[k] == value satisfies vec[i] < vec[k] <= vec[j].
    int i = 0;
    int j = vec.size() - 1;
    while (i <= j) {
      int mid = (j + i) / 2;
      int mid_value = vec.at(mid);
      // Enforces value is in vec[i], ..., vec[j].
      if (mid_value > value) {
        j = mid - 1;
      } else if (mid_value < value) {
        i = mid + 1;
      } else {
        // Enforces k for which vec[k] == value satisifes vec[i] < vec[k] <= vec[j].
        if (mid > 0 && vec.at(mid - 1) >= mid_value) {
          j = mid - 1;
        } else {
          result = mid;
          break;
        }
      }
    }

    return result;
  }
};

int main(int argc, char** argv) {
  BinarySearch search;
  std::vector<int> values = {0, 1, 2, 3, 3, 4};
  int value = 3;
  int result = search.Find(values, value);
  printf("result = %d\n", result);
  result = search.FindFirstOccurence(values, value);
  printf("result first occurence = %d\n", result);
  return 0;
}
