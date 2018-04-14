#pragma once

#include "Rectangle.h"

class Spacer : public Rect
{
public:
  Spacer(double, double);
  virtual std::string toPostScript() const override;
};