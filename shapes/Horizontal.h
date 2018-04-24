#pragma once

#include "Composite.h"
#include <vector>
#include <memory>

class Horizontal : public Composite
{
public:
  Horizontal(std::vector<std::unique_ptr<Shape>> &);
  virtual std::string toShape(unsigned int) const override;
  virtual std::string toCenter() const override;
  virtual double width() const override;
  virtual double height() const override;
private:
  std::vector<std::unique_ptr<Shape>> _shapes;
};
