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
//Vertical definitions
////////////////////////
Vertical::Vertical(std::vector<std::unique_ptr<Shape>> shapes) :_shapes(std::move(shapes))
{}

std::string Vertical::toPostScript() const
{
	std::ostringstream os;

	for (int i = 0; i < _shapes.size(); ++i)
	{
		os << _shapes[i]->toPostScript();

		if(i != _shapes.size() - 1)
			os << " 0 " << (_shapes[i]->height() / 2) + (_shapes[i + 1]->height() / 2) << " rmoveto \n";
	}

	return os.str();
}

double Vertical::width() const
{
	// width for vertical shape = width of the widest shape
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
	double total = 0.0;
	for (auto &shape : _shapes)
	{
		total = shape->height(); //changed this to be the last items height, so it can be used for stacking vertical
	}
	return total;
}

Scale::Scale(std::unique_ptr<Shape> shape, double fx, double fy) : _shape(std::move(shape)), _fx(fx), _fy(fy)
{}

// std::string Scale::toPostScript()
// {
// 	std::ostringstream os;

// 	os << _fx << " " << _fy << " scale \n";
// 	_shape->toPostScript();

// 	return os.str();
// }
