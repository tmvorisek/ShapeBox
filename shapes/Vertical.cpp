#include "Vertical.h"
#include <sstream>

Vertical::Vertical(std::vector<std::unique_ptr<Shape>> & shapes)
  : Composite::Composite(shapes)
{}

std::string Vertical::toPostScript() const
{
  return Composite::toPostScript();
}

std::string Vertical::toShape(unsigned int index) const
{
  std::ostringstream os;
  os  << " 0 " << (getShapeHeight(index) / 2) + (getShapeHeight(index + 1) / 2) 
      << " translate" << std::endl;
  return os.str();
}

std::string Vertical::toCenter() const
{
  std::ostringstream os;
  os << " 0 " << -height() / 2 << " translate\n"; //center object
  return os.str();
}

double Vertical::width() const
{
  double width = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    if (getShapeWidth(i) > width) width = getShapeWidth(i);
  }
  return width;
}

double Vertical::height() const
{
  double height = 0;
  for (unsigned int i = 0; i < getShapeCount(); i++)
  {
    height += getShapeHeight(i);
  }
  return height;
}
