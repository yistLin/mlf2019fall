#pragma once
#include "DataLoader.hpp"
#include <vector>

typedef std::vector<double> Weights;

class Regressor {
public:
  Regressor(int);
  ~Regressor();

  int predict(const DataLoader::Features &);
  void batchGradientDescent(const DataLoader::Dataset &, const double);
  void gradientDescent(const DataLoader::Features &, const DataLoader::Label &,
                       const double);
  double crossEntropyLoss(const DataLoader::Features &,
                          const DataLoader::Label &);

private:
  Weights weights;

  double product_(const DataLoader::Features &);
  double sigmoid_(const double);
  Weights gradient_(const DataLoader::Features &, const DataLoader::Label &);
  void updateWeight_(const Weights &, const double);
};
