#include "Regressor.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

Regressor::Regressor(int dim_input) {
  weights.resize(dim_input);
  std::fill(std::begin(weights), std::end(weights), 0.0);
}

Regressor::~Regressor() {}

double Regressor::crossEntropyLoss(const DataLoader::Features &x,
                                   const DataLoader::Label &y) {
  return std::log(1.0 + std::exp(-1.0 * static_cast<double>(y) * product_(x)));
}

int Regressor::predict(const DataLoader::Features &x) {
  return product_(x) > 0.0 ? 1 : -1;
}

void Regressor::gradientDescent(const DataLoader::Features &x,
                                const DataLoader::Label &y, const double eta) {
  Weights grad = gradient_(x, y);
  updateWeight_(grad, eta);
}

void Regressor::batchGradientDescent(const DataLoader::Dataset &dataset,
                                     const double eta) {
  Weights grads(std::size(weights), 0.0);
  for (const auto &[x, y] : dataset) {
    Weights grad = gradient_(x, y);
    std::transform(std::begin(grads), std::end(grads), std::begin(grad),
                   std::begin(grads), std::plus<double>());
  }
  std::for_each(std::begin(grads), std::end(grads), [&](double &g) {
    g /= static_cast<double>(std::size(dataset));
  });
  updateWeight_(grads, eta);
}

/* Private functions
 */

double Regressor::product_(const DataLoader::Features &x) {
  return std::inner_product(std::begin(x), std::end(x), std::begin(weights),
                            0.0) +
         weights.back();
}

double Regressor::sigmoid_(const double z) {
  return std::exp(z) / (1.0 + std::exp(z));
}

void Regressor::updateWeight_(const Weights &grad, const double eta) {
  std::transform(std::begin(weights), std::end(weights), std::begin(grad),
                 std::begin(weights),
                 [&](double w, double g) { return w - eta * g; });
}

Weights Regressor::gradient_(const DataLoader::Features &x,
                             const DataLoader::Label &y) {
  Weights grad(std::size(weights), 0.0);
  double ywx = sigmoid_(-1.0 * static_cast<double>(y) * product_(x));
  std::transform(std::begin(x), std::end(x), std::begin(grad), std::begin(grad),
                 [&](double xi, double g) {
                   return g + ywx * -1.0 * static_cast<double>(y) * xi;
                 });
  return grad;
}
