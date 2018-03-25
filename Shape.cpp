#include "Shape.h"
#include <sstream>

Shape::~Shape() = default;

////////////////////////
//Spacer definitions
////////////////////////
Spacer::Spacer(double width, double height) : _width(width), _height(height)
{}

std::string Spacer::toPostScript()
{
	std::ostringstream os;

	os  //<< "newpath 72 72 moveto " //this line might need to be handled by a wrapper function when making complex shapes

		<< 72 * _width << " 0 rlineto " //bottom
		<< " 0 " << 72 * _height << " rlineto " //right
		<< -72 * _width << " 0 rlineto " //top
		<< " closepath "; //completes left side, but doesnt draw

		//<< "showpage"; //this line will probably go into the wrapper function

	return os.str();
}

////////////////////////
//Rectangle definitions
////////////////////////
Rectangle::Rectangle(double width, double height): _width(width),_height(height)
{}

std::string Rectangle::toPostScript()
{
	std::ostringstream os;

	os  //<< "newpath 72 72 moveto " //this line might need to be handled by a wrapper function when making complex shapes

		<< 72 * _width << " 0 rlineto " //bottom
		<< " 0 " << 72 * _height << " rlineto " //right
		<< -72 * _width << " 0 rlineto " //top
		<< " closepath stroke "; //left and draw

		//<< "showpage"; //this line will probably go into the wrapper function

	return os.str();
}

////////////////////////
//Circle definitions
////////////////////////
Circle::Circle(double radius) :_radius(radius)
{}

std::string Circle::toPostScript()
{
	std::ostringstream os;

	os << " 0 0 " //origin of the circle. this needs to be able to change for complex shapes
		<< 72 * _radius 
		<< " 0 360 arc stroke ";

	return os.str();
}

////////////////////////
//Vertical definitions
////////////////////////
Vertical::Vertical(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{}

std::string Vertical::toPostScript()
{
	std::ostringstream os;

	for (auto & i : _shapes)
	{
		os<< i.toPostScript();
		//move origin based on current Shape's bounding box
		//do this by drawing an invisible spacer?
	}

	return os.str();
}