#include <iostream>
#include <sstream>
#include <array>
#include <vector>

using namespace std;

int main() {

    vector<array<float, 4>> xn;
    vector<float> yn;

    // parsing data
    string line;
    while (getline(cin, line)) {

        istringstream ss(line);
        array<float, 4> xtmp;
        float ytmp;

        ss >> xtmp.at(0) >> xtmp.at(1) >> xtmp.at(2) >> xtmp.at(3) >> ytmp;

        xn.push_back(xtmp);
        yn.push_back(ytmp);
    }

    return 0;
}
