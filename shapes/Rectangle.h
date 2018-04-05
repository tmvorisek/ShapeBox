#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height);
  virtual std::string toPostScript() const override;
  virtual double width() const override;
  virtual double height() const override;
private:
  const double _width, _height;
};