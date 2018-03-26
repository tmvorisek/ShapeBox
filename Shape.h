#pragma once

#include <string>
#include <memory>
#include <vector>

class Shape
{
public:
	virtual ~Shape();
	virtual std::string toPostScript() = 0;
};
//epooopop
//test
/////////////////////
//basic shape classes
/////////////////////
class Spacer : public Shape
{
public:
	Spacer(double width, double height);
	virtual std::string toPostScript();
private:
	double _width, _height;
};


class Rectangle : public Shape
{
public:
	Rectangle(double width, double height);
	virtual std::string toPostScript();
private:
	double _width, _height;
};


class Circle : public Shape
{
public:
	Circle(double radius);
	virtual std::string toPostScript();
private:
	double _radius;
};

////////////////////////
//compound shape classes
////////////////////////
class Vertical : public Shape
{
public:
	Vertical(std::vector<std::unique_ptr<Shape>> shapes);
	virtual std::string toPostScript();
private:
	std::vector<std::unique_ptr<Shape>> _shapes;
};
