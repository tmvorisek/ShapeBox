#include "Layered.h"
#include <sstream>

Layered::Layered(std::vector<std::unique_ptr<Shape>> & shapes)
  : Composite::Composite(shapes)
{}

std::string Layered::toPostScript() const
{
  return Composite::toPostScript();
}

std::string Layered::toShape(unsigned int index) const
{
  return "";
}

std::string Layered::toCenter() const
{
  return "";
}

double Layered::width() const
{
  double width = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    if (getShapeWidth(i) > width) width = getShapeWidth(i);
  }
  return width;
}

double Layered::height() const
{
  double height = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    if (getShapeHeight(i) > height) height = getShapeHeight(i);
  }
  return height;
}
