#pragma once

#include "Shape.h"

class Rect : public Shape
{
public:
  Rect(double width, double height);
  virtual std::string toPostScript() const override;
  virtual double width() const override;
  virtual double height() const override;
private:
  const double _width, _height;
};