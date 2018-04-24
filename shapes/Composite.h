#pragma once

#include "Shape.h"
#include <vector>
#include <memory>

class Composite : public Shape
{
public:
  Composite(std::vector<std::unique_ptr<Shape>> &);
  virtual std::string toPostScript() const override;
  virtual std::string toShape(unsigned int) const = 0;
  virtual std::string toCenter() const = 0;
  virtual unsigned int getShapeCount() const;
  virtual double getShapeWidth(unsigned int) const;
  virtual double getShapeHeight(unsigned int) const;
  virtual double width() const override = 0;
  virtual double height() const override = 0;
private:
  const std::vector<std::unique_ptr<Shape>> _shapes;
};
