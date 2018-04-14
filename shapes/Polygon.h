#pragma once

#include "Shape.h"

class Poly : public Shape
{
public:
  Poly(unsigned short, double);
  virtual std::string toPostScript() const override;
  virtual double width() const override;
  virtual double height() const override;
private:
  const unsigned short _sides;
  const double _sideLength;
};