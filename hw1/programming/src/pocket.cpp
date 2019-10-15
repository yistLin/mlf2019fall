#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <iomanip>

using namespace std;

array<float, 5> pocket(const vector<array<float, 5>>& x, const vector<int>& y, const vector<unsigned int>& cycle) {
    // initializing PLA
    array<float, 5> w = { 0 };
    array<float, 5> g = { 0 };

    // pocket iteration
    for (int c = 0, update_cnt = 0; update_cnt < 100; ++c < cycle.size() ? : c = 0) {

        // updating w
        float wtx = 0;
        for (int i = 0; i < 5; i++) {
            wtx += x[cycle[c]][i] * w[i];
        }
        if ((wtx > 0.0 ? 1 : -1) != y[cycle[c]]) {
            for (int i = 0; i < 5; i++) {
                w[i] += y[cycle[c]] * x[cycle[c]][i];
            }
            update_cnt++;
        }

        // accumulating errors
        int mistakes_w = 0, mistakes_g = 0;
        float gtx = 0;
        for (int i = 0; i < x.size(); i++) {
            wtx = gtx = 0;
            for (int j = 0; j < 5; j++)
                wtx += x[i][j] * w[j];
            for (int j = 0; j < 5; j++)
                gtx += x[i][j] * g[j];
            if ((wtx > 0.0 ? 1 : -1) != y[i])
                mistakes_w++;
            if ((gtx > 0.0 ? 1 : -1) != y[i])
                mistakes_g++;
        }

        // comparing mistakes two weights made and updating g
        if (mistakes_w < mistakes_g) {
            for (int i = 0; i < 5; i++)
                g[i] = w[i];
        }
    }

#ifdef RETURNW
    return w;
#else
    return g;
#endif
}

int main(int argc, const char* argv[]) {

    if (argc < 4) {
        cerr << "Error: # of command-line arguments should be 3" << endl;
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
    ifstream train_data_file;
    train_data_file.open(argv[2]);
    string line;
    while (getline(train_data_file, line)) {

        istringstream ss(line);
        array<float, 5> xtmp;
        int ytmp;

        xtmp[0] = 1;
        ss >> xtmp[1] >> xtmp[2] >> xtmp[3] >> xtmp[4] >> ytmp;

        xtrain.push_back(xtmp);
        ytrain.push_back(ytmp);
    }
    train_data_file.close();

    // parsing testing data
    ifstream test_data_file;
    test_data_file.open(argv[3]);
    while (getline(test_data_file, line)) {

        istringstream ss(line);
        array<float, 5> xtmp;
        int ytmp;

        xtmp[0] = 1;
        ss >> xtmp[1] >> xtmp[2] >> xtmp[3] >> xtmp[4] >> ytmp;

        xtest.push_back(xtmp);
        ytest.push_back(ytmp);
    }
    test_data_file.close();

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
            float wtx = 0;
            for (int k = 0; k < 5; k++) {
                wtx += xtest[j][k] * g_or_w[k];
            }
            if ((wtx > 0.0 ? 1 : -1) != ytest[j]) {
                error_cnt++;
            }
        }

        // output error rate
        cout << fixed << setprecision(1) << (float)error_cnt / (float)xtest.size() * 100.0 << "," << seed << endl;

        seed++;
    }

    return 0;
}
