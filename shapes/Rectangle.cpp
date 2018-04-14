#include "Rectangle.h"
#include <sstream>
//#include <cmath>

Rect::Rect(double width, double height) 
  : _width(std::abs(width)), _height(std::abs(height))
{}

std::string Rect::toPostScript() const
{
  std::ostringstream os;

  os
  << "gsave %<Rect>\n"
  << "newpath\n  "
  << -_width / 2 << " " << -_height / 2 << " moveto\n  "  //move to origin
  << _width << " 0 rlineto \n  " //bottom
  << "0 " << _height << " rlineto \n  " //right
  << -_width << " 0 rlineto \n" //top
  << "closepath\n"
  << "stroke \n"
  << "grestore  %</Rect>\n";

  return os.str();
}

double Rect::width() const
{
  return _width;
}

double Rect::height() const
{
  return _height;
}
