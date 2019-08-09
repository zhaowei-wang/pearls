#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> BitmapSort(const std::vector<int>& unsorted) {
  int max_value = INT_MIN;
  for (int value : unsorted) {
    max_value = std::max(max_value, value);
  }
  std::vector<bool> bitmap(max_value + 1, false);
  for (int value : unsorted) {
    bitmap[value] = true;
  }
  std::vector<int> sorted;
  for (int i = 0; i < bitmap.size(); ++i) {
    if (bitmap.at(i)) {
      sorted.push_back(i);     
    }
  }
  return sorted;
}


int main(int argc, char** argv) {
  constexpr int kMaxSize = 100000000;
  std::vector<int> unsorted(kMaxSize);
  std::iota(unsorted.begin(), unsorted.end(), 0);
  const auto sorted = BitmapSort(unsorted);
  return 0;
}
