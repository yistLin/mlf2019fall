#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace DataLoader {
typedef std::vector<std::tuple<std::vector<double>, int>> Dataset;
typedef std::tuple<std::vector<double>, int> DataPair;
typedef std::vector<double> Features;
typedef int Label;
Dataset load(const std::string &filename);
} // namespace DataLoader
