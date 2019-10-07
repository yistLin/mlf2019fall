#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

array<float, 5> pocket(const vector<array<float, 5>>& x, const vector<int>& y, const vector<unsigned int>& cycle, bool return_w) {
    // initializing PLA
    array<float, 5> w = { 0 };
    array<float, 5> g = { 0 };

    // pocket iteration
    for (int c = 0, update_cnt = 0; update_cnt < 100; c++) {

        if (c == cycle.size())
            c = 0;

        // updating w
        float wtx = 0;
        for (int i = 0; i < 5; i++) {
            wtx += x[c][i] * w[i];
        }
        if ((wtx > 0.0 ? 1 : -1) != y[c]) {
            for (int i = 0; i < 5; i++) {
                w[i] += y[c] * x[c][i];
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

    return return_w ? w : g;
}

int main(int argc, const char* argv[]) {

    // initializing
    int seed = 777;
    if (argc > 1) {
        seed = atoi(argv[1]);
    }
    bool return_w = false;
    if (argc > 2) {
        return_w = (bool)atoi(argv[2]);
    }
    vector<array<float, 5>> xn;
    vector<int> yn;

    // parsing data
    string line;
    while (getline(cin, line)) {

        istringstream ss(line);
        array<float, 5> xtmp;
        int ytmp;

        xtmp[0] = 1;

        ss >> xtmp[1] >> xtmp[2] >> xtmp[3] >> xtmp[4] >> ytmp;

        xn.push_back(xtmp);
        yn.push_back(ytmp);
    }

    // printing out csv column title
    /* cout << "update,seed" << endl; */

    // running experiments for 1126 times
    for (int i = 0; i < 1126; i++) {

        // randomly shuffling data
        vector<unsigned int> cycle(xn.size());
        iota(cycle.begin(), cycle.end(), 0);
        shuffle(cycle.begin(), cycle.end(), default_random_engine(seed));

        // running Pocket
        auto g_or_w = pocket(xn, yn, cycle, return_w);

        seed++;
    }

    return 0;
}
