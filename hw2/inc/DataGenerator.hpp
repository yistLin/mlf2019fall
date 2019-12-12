#pragma once
#include <random>

#include "Data.hpp"

class DataGenerator {
 private:
  std::default_random_engine rand_eng;
  std::uniform_real_distribution<double> dist_input;
  std::uniform_real_distribution<double> dist_noise;

 public:
  DataGenerator(unsigned seed)
      : rand_eng(seed), dist_input(-1.0, 1.0), dist_noise(0.0, 1.0) {}
  virtual ~DataGenerator();

  // functions
  Data operator()();
};
