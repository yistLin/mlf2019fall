#include "DataGenerator.hpp"

DataGenerator::~DataGenerator() {}

Data DataGenerator::operator()() {
  double x = dist_input(rand_eng);
  int y = x > 0.0 ? 1 : -1;
  y = dist_noise(rand_eng) > 0.2 ? y : -y;
  return Data(x, y);
}
