#include <algorithm>
#include <iostream>
#include <vector>

#include "Data.hpp"
#include "DataGenerator.hpp"

int main() {
  DataGenerator generator(777);
  std::vector<Data> data(20);
  std::generate(data.begin(), data.end(), generator);

  for (auto d : data) {
    std::cout << d.x << " " << d.y << std::endl;
  }

  return 0;
}
