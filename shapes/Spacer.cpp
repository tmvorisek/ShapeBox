#include "Spacer.h"

Spacer::Spacer(double width, double height)
  : Rect(width, height)
{}

std::string Spacer::toPostScript() const
{
  return "";
}
