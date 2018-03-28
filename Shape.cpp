#include "Shape.h"
#include <sstream>

Shape::~Shape() = default;

////////////////////////
//Spacer definitions
////////////////////////
Spacer::Spacer(double width, double height) : _width(width), _height(height)
{}

std::string Spacer::toPostScript() const
{
	std::ostringstream os;

	os  << "newpath " // 72 72 moveto " //this line might need to be handled by a wrapper function when making complex shapes

		<< _width << " 0 rlineto \n" //bottom
		<< " 0 " << _height << " rlineto \n" //right
		<< _width << " 0 rlineto \n" //top
		<< " closepath \n"; //completes left side, but doesnt draw

		//<< "showpage"; //this line will probably go into the wrapper function

	return os.str();
}

double Spacer::width() const
{
	return _width;
}

double Spacer::height() const
{
	return _height;
}


////////////////////////
//Rectangle definitions
////////////////////////
Rectangle::Rectangle(double width, double height): _width(width),_height(height)
{}

std::string Rectangle::toPostScript() const
{
	std::ostringstream os;

	os << "gsave \n"
		<< _width << " 0 rlineto \n" //bottom
		<< " 0 " << _height << " rlineto \n" //right
		<< _width << " 0 rlineto \n" //top
		<< "  stroke \n" //left
		<< "grestore \n";

	return os.str();
}

double Rectangle::width() const
{
	return _width;
}

double Rectangle::height() const
{
	return _height;
}

////////////////////////
//Circle definitions
////////////////////////
Circle::Circle(double radius) :_radius(radius)
{}

std::string Circle::toPostScript() const
{
	std::ostringstream os;

	os << " currentpoint " << _radius << " 0 360 arc stroke \n";

	return os.str();
}

double Circle::width() const
{
	return 2*_radius;
}

double Circle::height() const
{
	return 2*_radius;
}


////////////////////////
//Vertical definitions
////////////////////////
Vertical::Vertical(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{}

std::string Vertical::toPostScript() const
{
	std::ostringstream os;

	for (auto & i : _shapes)
	{
		os << i->toPostScript();
		//move origin based on current Shape's bounding box
		//do this by drawing an invisible spacer?
	}

	return os.str();
}

double Vertical::width() const
{
	return 1;
}

double Vertical::height() const
{	
	double total =0;
	for (auto const &shape: _shapes) 
	{
		total+=shape->height;
	}
	return total;
}

Scale::Scale(std::unique_ptr<Shape> shape, double fx, double fy): _shape(std::move(shape)), _fx(fx), _fy(fy)
{}

std::string Scale::toPostScript()
{
	std::ostringstream os;

	os << _fx << " " << _fy << " scale \n";
	_shape->toPostScript();

	return os.str();
}
