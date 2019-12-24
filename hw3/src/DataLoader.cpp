#include "DataLoader.hpp"

DataLoader::Dataset DataLoader::load(const std::string &filename) {
  std::ifstream fs(filename);
  std::string line;
  Dataset dataset;

  if (fs.is_open()) {
    while (std::getline(fs, line)) {
      std::istringstream ss(line);
      std::vector<double> x_tmp(20);
      int y_tmp;
      ss >> x_tmp[0] >> x_tmp[1] >> x_tmp[2] >> x_tmp[3] >> x_tmp[4] >>
          x_tmp[5] >> x_tmp[6] >> x_tmp[7] >> x_tmp[8] >> x_tmp[9] >>
          x_tmp[10] >> x_tmp[11] >> x_tmp[12] >> x_tmp[13] >> x_tmp[14] >>
          x_tmp[15] >> x_tmp[16] >> x_tmp[17] >> x_tmp[18] >> x_tmp[19] >>
          y_tmp;
      dataset.push_back({x_tmp, y_tmp});
    }
    fs.close();
  }

  return dataset;
}
