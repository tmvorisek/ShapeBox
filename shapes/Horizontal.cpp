#include "Horizontal.h"
#include <sstream>

Horizontal::Horizontal(std::vector<std::unique_ptr<Shape>> & shapes)
  : Composite::Composite(shapes)
{}

std::string Horizontal::toShape(unsigned int index) const
{
  std::ostringstream os;
  os  << (getShapeHeight(index) / 2) + (getShapeHeight(index + 1) / 2) 
      << " 0 translate \n";
  return os.str();
}

std::string Horizontal::toCenter() const
{
  std::ostringstream os;
  os << -width() / 2 << " 0  translate \n";  //center the horizontal shape 
  return os.str();
}

double Horizontal::width() const
{
  double width = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    width += getShapeWidth(i);
  }
  return width;
}

double Horizontal::height() const
{
  double height = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    if (getShapeHeight(i) > height) height = getShapeHeight(i);
  }
  return height;
}
