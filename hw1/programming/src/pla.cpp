#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

int pla(const vector<array<float, 5>> &x, const vector<int> &y,
        const vector<unsigned int> &cycle) {
  // initializing PLA
  array<float, 5> w = {0};
  int n_update = 0;

  // updating w
  bool no_mistake = false;
  while (!no_mistake) {
    no_mistake = true;
    for (auto c : cycle) {
      float wtx = inner_product(x[c].begin(), x[c].end(), w.begin(), 0.0);
      if ((wtx > 0.0 ? 1 : -1) != y[c]) {
        transform(w.begin(), w.end(), x[c].begin(), w.begin(),
                  [&](float a, float b) { return a + (float)y[c] * b; });
        no_mistake = false;
        n_update++;
      }
    }
  }

  return n_update;
}

int main(int argc, const char *argv[]) {

  if (argc != 3) {
    cerr << "Usage: ./pla <RANDOM_SEED> <DATA_PATH>" << endl;
    return 1;
  }

  // initializing
  ifstream data_stream;
  int seed = atoi(argv[1]);
  data_stream.open(argv[2]);
  vector<array<float, 5>> xn;
  vector<int> yn;

  // parsing data
  array<float, 5> xin = {1, 0, 0, 0, 0};
  int yin;
  while (data_stream >> xin[1] >> xin[2] >> xin[3] >> xin[4] >> yin) {
    xn.push_back(xin);
    yn.push_back(yin);
  }
  data_stream.close();

  // printing out csv column title
  cout << "update,seed" << endl;

  // running experiments for 1126 times
  for (int i = 0; i < 1126; i++, seed++) {

    // randomly shuffling data
    vector<unsigned int> cycle(xn.size());
    iota(cycle.begin(), cycle.end(), 0);
    shuffle(cycle.begin(), cycle.end(), default_random_engine(seed));

    // running PLA
    int n_update = pla(xn, yn, cycle);

    // printing out a row of csv
    cout << n_update << "," << seed << endl;
  }

  return 0;
}
