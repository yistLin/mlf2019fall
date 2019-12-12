#pragma once

class Data {
 public:
  Data() : x(0.0), y(1) {}
  Data(double x, int y) : x(x), y(y) {}
  double x;
  int y;
};