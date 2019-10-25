#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

constexpr int SIGN(float f) { return (f > 0.0) ? 1 : -1; }

array<float, 5> pocket(const vector<array<float, 5>> &x, const vector<int> &y,
                       const vector<unsigned int> &cycle) {
  // initializing PLA
  array<float, 5> w = {0};
  array<float, 5> g = {0};

  // pocket iteration
  for (int c = 0, update_cnt = 0; update_cnt < 100;
       ++c < cycle.size() ?: c = 0) {

    // updating w
    float wtx = inner_product(x[cycle[c]].begin(), x[cycle[c]].end(), w.begin(), 0.0);
    if (SIGN(wtx) != y[cycle[c]]) {
      transform(w.begin(), w.end(), x[cycle[c]].begin(), w.begin(),
                [&](float a, float b) { return a + (float)y[cycle[c]] * b; });
      update_cnt++;
    }

    // accumulating errors
    int mistakes_w = 0, mistakes_g = 0;
    for (int i = 0; i < x.size(); i++) {
      wtx = inner_product(x[i].begin(), x[i].end(), w.begin(), 0.0);
      float gtx = inner_product(x[i].begin(), x[i].end(), g.begin(), 0.0);
      if (SIGN(wtx) != y[i])
        mistakes_w++;
      if (SIGN(gtx) != y[i])
        mistakes_g++;
    }

    // comparing mistakes two weights made and updating g
    if (mistakes_w < mistakes_g) {
      copy(w.begin(), w.end(), g.begin());
    }
  }

#ifdef RETURNW
  return w;
#else
  return g;
#endif
}

int main(int argc, const char *argv[]) {

  if (argc != 4) {
    cerr << "Usage: ./pocket SEED TRAIN_DATA_FILE TEST_DATA_FILE" << endl;
    return 1;
  }

  // initializing
  int seed = atoi(argv[1]);
  vector<array<float, 5>> xtrain;
  vector<int> ytrain;
  vector<array<float, 5>> xtest;
  vector<int> ytest;

  // parsing training data
  ifstream data_stream;
  array<float, 5> xin = { 1, 0, 0, 0, 0 };
  int yin;
  data_stream.open(argv[2]);
  while (data_stream >> xin[1] >> xin[2] >> xin[3] >> xin[4] >> yin) {
    xtrain.push_back(xin);
    ytrain.push_back(yin);
  }
  data_stream.close();

  // parsing testing data
  data_stream.open(argv[3]);
  while (data_stream >> xin[1] >> xin[2] >> xin[3] >> xin[4] >> yin) {
    xtest.push_back(xin);
    ytest.push_back(yin);
  }
  data_stream.close();

  // printing out csv column title
  cout << "error_rate,seed" << endl;

  // running experiments for 1126 times
  for (int i = 0; i < 1126; i++) {

    // randomly shuffling data according to random seed
    vector<unsigned int> cycle(xtrain.size());
    iota(cycle.begin(), cycle.end(), 0);
    shuffle(cycle.begin(), cycle.end(), default_random_engine(seed));

    // running Pocket algorithm
    auto g_or_w = pocket(xtrain, ytrain, cycle);

    // verifying on test set
    int error_cnt = 0;
    for (int j = 0; j < xtest.size(); j++) {
      float wtx = inner_product(xtest[j].begin(), xtest[j].end(), g_or_w.begin(), 0.0);
      if (SIGN(wtx) != ytest[j]) {
        error_cnt++;
      }
    }

    // output error rate
    cout << fixed << setprecision(1)
         << (float)error_cnt / (float)xtest.size() * 100.0 << "," << seed
         << endl;

    seed++;
  }

  return 0;
}
