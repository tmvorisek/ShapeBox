#include "Rectangle.h"
#include <sstream>
#include <cmath>

Rectangle::Rectangle(double width, double height) : _width(width), _height(height)
{}

std::string Rectangle::toPostScript() const
{
  std::ostringstream os;

  os<< "gsave %<rectangle>\n"
    << "newpath\n  "
    << -_width / 2 << " " << -_height / 2 << " moveto\n  "  //move to origin
    << _width << " 0 rlineto \n  " //bottom
    << "0 " << _height << " rlineto \n  " //right
    << -_width << " 0 rlineto \n" //top
    << "closepath\n"
    << "stroke \n"
    << "grestore  %</rectangle>\n";

  return os.str();
}

double Rectangle::width() const
{
  return std::abs(_width);
}

double Rectangle::height() const
{
  return std::abs(_height);
}
