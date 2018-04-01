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

	os << "gsave \n"
		<< -_width / 2 << " " << -_height / 2 << " rmoveto \n"
		<< _width << " 0 rlineto \n" //bottom
		<< " 0 " << _height << " rlineto \n" //right
		<< -_width << " 0 rlineto \n" //top
		<< " 0 " << -_height << " rlineto \n"  //left 
		<< "grestore \n";

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
Rectangle::Rectangle(double width, double height) : _width(width), _height(height)
{}

std::string Rectangle::toPostScript() const
{
	std::ostringstream os;

	os
		<< "gsave \n"
		<< -_width / 2 << " " << -_height / 2 << " rmoveto \n"  //move to origin
		<< _width << " 0 rlineto \n" //bottom
		<< " 0 " << _height << " rlineto \n" //right
		<< -_width << " 0 rlineto \n" //top
		<< " 0 " << -_height << " rlineto \n"  //left 
		<< "  stroke \n"
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
//Square definitions
////////////////////////
Square::Square(double length) :Rectangle(length, length) {}

////////////////////////
//Circle definitions
////////////////////////
Circle::Circle(double radius) : _radius(radius)
{}

std::string Circle::toPostScript() const
{
	std::ostringstream os;

	os << "gsave \n" //compound shapes break if you dont have gsave and restore
		<< " currentpoint " << _radius << " 0 360 arc stroke \n"
		<< "grestore \n";

	return os.str();
}

double Circle::width() const
{
	return 2 * _radius;
}

double Circle::height() const
{
	return 2 * _radius;
}

////////////////////////
//Polygon definitions
////////////////////////
Polygon::Polygon(unsigned int sides, double sideLength)
	: _sides(sides), _sideLength(sideLength)
{}

std::string Polygon::toPostScript() const
{
	std::ostringstream os;


	return os.str();
}

double Polygon::width() const
{
	return 0;
}

double Polygon::height() const
{
	return 0;
}

////////////////////////
//Vertical definitions
////////////////////////

Vertical::Vertical(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{}

std::string Vertical::toPostScript() const
{
	std::ostringstream os;

	os << "gsave \n";
	os << " 0 " << -height() / 2 << " rmoveto \n"; //center object
	for (int i = 0; i < _shapes.size(); ++i)
	{
		os << _shapes[i]->toPostScript();

		if (i != _shapes.size() - 1)
			os << " 0 " << (_shapes[i]->height() / 2) + (_shapes[i + 1]->height() / 2) << " rmoveto \n";
	}
	os << "grestore \n";


	return os.str();
}

double Vertical::width() const
{
	//width for vertical shape = width of the widest shape
	double result = 0;

	for (auto & shape : _shapes)
	{
		if (result < shape->width())
			result = shape->width();
	}

	return result;
}

double Vertical::height() const
{
	double total = 0;
	for (auto &shape : _shapes)
	{
		total += shape->height();
	}
	return total;
}

Horizontal::Horizontal(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{}

std::string Horizontal::toPostScript() const
{
	std::ostringstream os;

	os << "gsave \n";
	os << -width() / 2 << " 0  rmoveto \n";  //center the horizontal shape 
	for (int i = 0; i < _shapes.size(); ++i)
	{
		os << _shapes[i]->toPostScript();

		if (i != _shapes.size() - 1)
			os << (_shapes[i]->width() / 2) + (_shapes[i + 1]->width() / 2) << " 0 rmoveto \n";
	}
	os << "grestore \n";

	return os.str();
}

double Horizontal::width() const
{
	double total = 0;
	for (auto &shape : _shapes)
	{
		total += shape->width();
	}
	return total;
}

double Horizontal::height() const
{
	//horizontal width = width of the widest shape in vector
	double result = 0;
	for (auto & shape : _shapes)
	{
		if (result < shape->height())
			result = shape->height();
	}

	return result;
}


Scale::Scale(std::unique_ptr<Shape> shape, double scaleX, double scaleY) : _shape(std::move(shape)), _scaleX(scaleX), _scaleY(scaleY)
{}

std::string Scale::toPostScript() const 
{	
	std::ostringstream os;

	 os << "gsave \n"
		<< _scaleX << " " << _scaleY << " scale \n"
		<< -width() / 2.0 << " " << -height() / 2.0 << " rmoveto \n"  //move to origin
		<< _shape->toPostScript() << " \n"
		<< "grestore \n";

	return os.str();
}

double Scale::width() const
{
	return _shape->width() * _scaleX;
}

double Scale::height() const
{
	return _shape->height() * _scaleY;
}

Rotate::Rotate(std::unique_ptr<Shape> shape, int angle) : _shape(std::move(shape)), _angle(angle)
{
	if (angle != 90 && angle != 180 && angle != 270)
		_angle = 0;
}

int Rotate::angle() const {
	return _angle;
}

std::string Rotate::toPostScript() const
{
	std::ostringstream os;
	os << "gsave \n"
		<< -_width / 2 << " " << -_height / 2 << " rmoveto \n"  //move to origin
		<< angle() << " rotate \n"
		<< _shape->toPostScript()
		<< "grestore \n";

	return os.str();
}

double Rotate::width() const {
	if (angle() == 90 || angle() == 270)
		return _shape->height();
	else
		return _shape->width();
}

double Rotate::height() const {
	if (angle() == 90 || angle() == 270)
		return _shape->width();
	else
		return _shape->height();
}

Translation::Translation(std::unique_ptr<Shape> shape, double dx, double dy)
	: _shape(std::move(shape)), _dx(dx), _dy(dy)
{}

std::string Translation::toPostScript() const
{
	std::ostringstream os;

	os << "gsave\n" << _dx << " " << _dy << " translate\n";
	os << _shape->toPostScript() << "grestore\n";

	return os.str();
}

double Translation::width() const
{
	return _shape->width();
}

double Translation::height() const
{
	return _shape->height();
}
