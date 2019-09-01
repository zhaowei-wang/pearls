#include <iostream>
#include <vector>

void swap(std::vector<int>* data, int i, int j) {
  int tmp = data->at(i);
  (*data)[i] = data->at(j);
  (*data)[j] = tmp;
}

/*
  Maintain the following invariant:

  [    x[k] < t   |    x[k] >= t    |     ?     ]
                 ^ m                 ^ i
 */
int partition(std::vector<int>* data, int split_value) {
  int m = 0;
  for (int i = 0; i < data->size(); ++i) {
    if ((*data)[i] < split_value )
      swap(data, i, m++);
  }
  return m;
}

int main(int argc, char** argv) {
  std::vector<int> data = {8, 3, 2, 10, 15, 4};
  std::cout << partition(&data, 5) << std::endl;
  for (const int value : data)
    std::cout << value << " ";
  std::cout << std::endl;
  return 0;
}
