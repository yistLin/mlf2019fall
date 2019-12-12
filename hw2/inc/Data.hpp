#pragma once

class Data {
 public:
  Data() : x(0.0), y(0.0) {}
  Data(double x, double y) : x(x), y(y) {}
  double x, y;
};