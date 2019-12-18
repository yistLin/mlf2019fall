#include "DataGenerator.hpp"

DataGenerator::~DataGenerator() {}

Data DataGenerator::operator()() {
  double x = m_inputDist(m_randomEngine);
  int y = x > 0.0 ? 1 : -1;
  y = m_noiseDist(m_randomEngine) > 0.2 ? y : -y;
  return Data(x, y);
}
