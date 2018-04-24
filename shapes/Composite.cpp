#include "Composite.h"
#include <sstream>

#include <iostream>

Composite::Composite(std::vector<std::unique_ptr<Shape>> & shapes)
  : _shapes(std::move(shapes))
{}

std::string Composite::toPostScript() const
{
  std::ostringstream os;

  os << "gsave %<Composite> \n";
  os << toCenter() << std::endl;
  for (unsigned int i = 0; i < _shapes.size(); ++i)
  {
    os << "gsave %<Composite> \n";
    os << _shapes[i]->toPostScript();
    os << "grestore %<Composite> \n";

    if (i != _shapes.size() - 1)
      os << toShape(i);

  }
  os << "grestore %<Composite> \n";

  return os.str();
}

unsigned int Composite::getShapeCount() const
{
  return _shapes.size();
}


double Composite::getShapeWidth(unsigned int index) const
{
  return _shapes[index]->width();
}

double Composite::getShapeHeight(unsigned int index) const
{
  return _shapes[index]->height();
}  
