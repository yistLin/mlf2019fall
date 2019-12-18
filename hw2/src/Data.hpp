#pragma once

struct Data {
  double x = 0.0;
  int y = 0;

  Data() {};
  Data(double t_x, int t_y) : x(t_x), y(t_y) {}
};
