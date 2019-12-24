#include "DataLoader.hpp"
#include "Regressor.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "More than 1 command-line arguments are expected!" << endl;
    exit(1);
  }

  const string filename(argv[1]);
  DataLoader::Dataset train_data = DataLoader::load(filename);

  if (size(train_data) > 0) {
    cout << "size of training data = " << size(train_data) << endl << endl;

    DataLoader::Dataset tiny_train_data(begin(train_data),
                                        begin(train_data) + 10);

    cout << "Data:" << endl;
    for (auto &[x, y] : tiny_train_data) {
      for (auto xi : x) {
        cout << xi << " ";
      }
      cout << y << endl;
    }
    cout << endl;

    Regressor regressor(20);

    cout << "Prediction:" << endl;
    for (auto &[x, y] : tiny_train_data) {
      cout << regressor.predict(x) << endl;
    }
    cout << endl;

    cout << "Cross-Entropy Loss:" << endl;
    for (auto &[x, y] : tiny_train_data) {
      cout << regressor.crossEntropyLoss(x, y) << endl;
    }
    cout << endl;

    for (int i = 0; i < 2000; i++) {
      regressor.batchGradientDescent(train_data, 0.01);
    }
    cout << "After 1000 step of gradient descent..." << endl << endl;

    cout << "Prediction:" << endl;
    int num_error = 0;
    for (auto &[x, y] : tiny_train_data) {
      int pred = regressor.predict(x);
      cout << pred << endl;
      if (pred != y)
        num_error++;
    }
    cout << "E_in = "
         << static_cast<double>(num_error) /
                static_cast<double>(size(tiny_train_data))
         << endl;
    cout << endl;

    cout << "Cross-Entropy Loss:" << endl;
    for (auto &[x, y] : tiny_train_data) {
      cout << regressor.crossEntropyLoss(x, y) << endl;
    }
    cout << endl;
  }

  return 0;
}
