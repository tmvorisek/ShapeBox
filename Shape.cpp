#define _USE_MATH_DEFINES

#include "Shape.h"
#include <sstream>
#include <math.h>
#include <stdexcept>


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
		<< "gsave %<rectangle>\n"
		<< -_width / 2 << " " << -_height / 2 << " rmoveto \n"  //move to origin
		<< _width << " 0 rlineto \n" //bottom
		<< " 0 " << _height << " rlineto \n" //right
		<< -_width << " 0 rlineto \n" //top
		<< " 0 " << -_height << " rlineto \n"  //left 
		<< "  stroke \n"
		<< "grestore  %</rectangle>\n";

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

	os << "gsave %<circle> \n" //compound shapes break if you dont have gsave and restore
		<< "currentpoint " << _radius << " 0 360 arc stroke \n"
		<< "grestore %</circle> \n";

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
{
	if (_sides<3)
	{
		throw std::invalid_argument( "Polygons must have 3 or more sides" );
	}
}

std::string Polygon::toPostScript() const
{
	const double o = _sideLength/2, theta = 360/_sides;
	const double a = o/std::tan(theta/2);
	const double h = std::atan(o/a)*180/M_PI;
	std::ostringstream os;
	os << "gsave % <polygon>\n";


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
{
	for (auto & shape : _shapes)
	{
		_height += shape->height();

		if (_width < shape->width())
			_width = shape->width();
	}
}

std::string Vertical::toPostScript() const
{
	std::ostringstream os;

	os << "gsave %<vertical>\n";
	os << " 0 " << -height() / 2 << " rmoveto \n"; //center object
	for (int i = 0; i < _shapes.size(); ++i)
	{
		os << _shapes[i]->toPostScript();

		if (i != _shapes.size() - 1)
			os << " 0 " << (_shapes[i]->height() / 2) + (_shapes[i + 1]->height() / 2) << " rmoveto \n";
	}
	os << "grestore %</vertical> \n";


	return os.str();
}

double Vertical::width() const
{
	return _width;
}

double Vertical::height() const
{
	return _height;
}

Horizontal::Horizontal(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{
	for (auto &shape : _shapes)
	{
		_width += shape->width();

		if (_height < shape->height())
			_height = shape->height();
	}
}

std::string Horizontal::toPostScript() const
{
	std::ostringstream os;

	os << "gsave %<horizontal> \n";
	os << -width() / 2 << " 0  rmoveto \n";  //center the horizontal shape 
	for (int i = 0; i < _shapes.size(); ++i)
	{
		os << _shapes[i]->toPostScript();

		if (i != _shapes.size() - 1)
			os << (_shapes[i]->width() / 2) + (_shapes[i + 1]->width() / 2) << " 0 rmoveto \n";
	}
	os << "grestore %</horizontal> \n";

	return os.str();
}

double Horizontal::width() const
{
	return _width;
}

double Horizontal::height() const
{
	return _height;
}


Scale::Scale(std::unique_ptr<Shape> shape, double scaleX, double scaleY) : _shape(std::move(shape)), _scaleX(scaleX), _scaleY(scaleY)
{
	_width = _shape->width() * scaleX;
	_height = _shape->height() * scaleY;
}

std::string Scale::toPostScript() const 
{	
	std::ostringstream os;

	 os << "gsave %<scale> \n"
		<< _scaleX << " " << _scaleY << " scale \n"
		<< _shape->toPostScript() << " \n"
		<< "grestore %</scale> \n";

	return os.str();
}

double Scale::width() const
{
	return _width;
}

double Scale::height() const
{
	return _height;
}

Rotate::Rotate(std::unique_ptr<Shape> shape, int angle) : _shape(std::move(shape)), _angle(angle)
{
	_width = _shape->width();
	_height = _shape->height();

	if (angle != 90 && angle != 180 && angle != 270)
		_angle = 0;

	if (_angle == 90 || _angle == 270)
	{
		_width = _shape->height();
		_height = _shape->width();
	}
}

int Rotate::angle() const {
	return _angle;
}

std::string Rotate::toPostScript() const
{
	std::ostringstream os;
	os << "gsave %<rotate> \n"
		<< angle() << " rotate \n"
		//<< -width() / 2 << "  " << -height() / 2 << " rmoveto \n"  //move to origin
		<< _shape->toPostScript()
		<< "grestore %</rotate> \n";

	return os.str();
}

double Rotate::width() const 
{
	return _width;
}

double Rotate::height() const 
{
	return _height;
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
