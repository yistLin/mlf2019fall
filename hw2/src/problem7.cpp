#include <algorithm>
#include <array>
#include <iostream>
#include "DataGenerator.hpp"

using namespace std;

int main() {
  DataGenerator generator(777);
  array<double, 20> data;
  generate(data.begin(), data.end(), generator);

  for (auto d : data) {
    cout << d << endl;
  }

  return 0;
}
