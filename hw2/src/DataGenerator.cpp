#include "DataGenerator.hpp"

DataGenerator::~DataGenerator() {}

double DataGenerator::operator()() {
  return rand_dist(rand_eng);
}
