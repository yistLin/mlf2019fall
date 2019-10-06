#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

int pla(const vector<array<float, 5>>& x, const vector<int>& y, const vector<unsigned int>& cycle) {
    // initializing PLA
    array<float, 5> w = { 0 };
    bool no_mistake = false;
    int update_cnt = 0;

    // updating w
    while (!no_mistake) {
        no_mistake = true;

        for (int c : cycle) {
            float wtx = 0;
            for (int i = 0; i < 5; i++) {
                wtx += x[c][i] * w[i];
            }

            int sign = (wtx > 0.0) ? 1 : -1;
            if (sign != y[c]) {
                for (int i = 0; i < 5; i++) {
                    w[i] += y[c] * x[c][i];
                }
                no_mistake = false;
                update_cnt++;
            }
        }
    }

    return update_cnt;
}

int main(int argc, const char* argv[]) {

    // initializing
    int seed = 777;
    if (argc > 1) {
        seed = atoi(argv[1]);
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

    // running experiments for 1126 times
    int update_total = 0;
    for (int i = 0; i < 1126; i++) {

        // randomly shuffling data
        vector<unsigned int> cycle(xn.size());
        iota(cycle.begin(), cycle.end(), 0);
        shuffle(cycle.begin(), cycle.end(), default_random_engine(seed));

        // running PLA
        int update_cnt = pla(xn, yn, cycle);
        update_total += update_cnt;

        seed++;
    }

    cout << (float)update_total / 1126 << endl;

    return 0;
}
