#pragma once
#include <random>

class DataGenerator {
private:
  std::default_random_engine rand_eng;
  std::uniform_real_distribution<double> rand_dist;

public:
  DataGenerator(unsigned seed): rand_eng(seed), rand_dist(-1.0, 1.0) {}
  virtual ~DataGenerator();

  // functions
  double operator()();
};
