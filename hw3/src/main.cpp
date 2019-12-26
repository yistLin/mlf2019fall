#include "DataLoader.hpp"
#include "Regressor.hpp"
#include <iostream>
#include <numeric>
using namespace std;

double error_rate(Regressor regressor, const DataLoader::Dataset &dataset) {
  int num_error =
      accumulate(begin(dataset), end(dataset), 0, [&](int a, auto b) {
        return a + static_cast<int>(regressor.predict(get<0>(b)) != get<1>(b));
      });
  return static_cast<double>(num_error) / static_cast<double>(size(dataset));
}

int main(int argc, char *argv[]) {
  const string train_filename(argv[1]);
  const string test_filename(argv[2]);

  DataLoader::Dataset train_data = DataLoader::load(train_filename);
  DataLoader::Dataset test_data = DataLoader::load(test_filename);

  Regressor regressor1(20), regressor2(20);

  cout << "t,batch,stochastic" << endl;

  auto data_ptr = begin(train_data);
  for (int i = 0; i < 2000; i++) {

    // gradient descent
    regressor1.batchGradientDescent(train_data, 0.01);

    // stochastic gradient descent
    data_ptr = (data_ptr == end(train_data)) ? begin(train_data) : data_ptr + 1;
    const auto &[xi, yi] = *data_ptr;
    regressor2.gradientDescent(xi, yi, 0.001);

    cout << i + 1 << ",";
#ifdef PROBLEM7
    cout << error_rate(regressor1, train_data) << ",";
    cout << error_rate(regressor2, train_data) << endl;
#elif PROBLEM8
    cout << error_rate(regressor1, test_data) << ",";
    cout << error_rate(regressor2, test_data) << endl;
#endif
  }

  return 0;
}
