#pragma once
#include <random>

#include "Data.hpp"

class DataGenerator {
 public:
  DataGenerator(unsigned t_seed)
    : m_randomEngine(t_seed), m_inputDist(-1.0, 1.0), m_noiseDist(0.0, 1.0) {}
  virtual ~DataGenerator();

  Data operator()();

 private:
  std::default_random_engine m_randomEngine;
  std::uniform_real_distribution<double> m_inputDist;
  std::uniform_real_distribution<double> m_noiseDist;
};
