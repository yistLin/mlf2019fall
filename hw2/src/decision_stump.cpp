#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Data.hpp"
#include "DataGenerator.hpp"

using namespace std;

double errorRate(const vector<Data>& data, int s, double theta) {
  int n_error = 0;
  for (auto [x, y] : data) {
    if (s * int(x > theta) != y) n_error++;
  }
  return double(n_error) / double(data.size());
}

double errorRateOut(int s, double theta) {
  return 0.5 + 0.3 * double(s) * (abs(theta) - 1.0);
}

tuple<int, double> decisionStump(const vector<Data>& data) {
  // calculate right boundaries
  vector<double> right_bounds(data.size());
  transform(data.begin(), data.end(), right_bounds.begin(),
            [](Data d) -> double { return d.x; });
  right_bounds.push_back(2.0);

  // find s and theta that leads to the lowest E_in
  int s_best = 0;
  double theta_best = -2.0, left = -2.0, lowest_error_rate = 1.0;
  for (auto right : right_bounds) {
    double theta_tmp = (left + right) / 2.0;
    for (int s_tmp : {-1, 1}) {
      double error_rate = errorRate(data, s_tmp, theta_tmp);
      if (error_rate < lowest_error_rate) {
        lowest_error_rate = error_rate;
        s_best = s_tmp;
        theta_best = theta_tmp;
      }
    }
    left = right;
  }

  return {s_best, theta_best};
}

int main(int argc, char* const argv[]) {
  assert(argc > 1);
  int n_data = atoi(argv[1]);

  // initialize data set generator
  DataGenerator generator(777);

  // run experiment for 1000 times
  for (int i = 0; i < 1000; i++) {
    // generate artificial data set
    vector<Data> data(n_data);
    generate(data.begin(), data.end(), [&]() { return generator(); });
    sort(data.begin(), data.end(), [](auto a, auto b) { return a.x < b.x; });

    // find the best hypothesis
    auto [s, theta] = decisionStump(data);
    cout << errorRate(data, s, theta) - errorRateOut(s, theta) << endl;
  }

  return 0;
}
