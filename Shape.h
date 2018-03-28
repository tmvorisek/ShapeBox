#pragma once

#include <string>
#include <memory>
#include <vector>

class Shape
{
public:
	virtual ~Shape();
	virtual std::string toPostScript() const = 0;
	virtual double width() const = 0;
	virtual double height() const = 0;
};


/////////////////////
//basic shape classes
/////////////////////
class Spacer : public Shape
{
public:
	Spacer(double width, double height);
	virtual std::string toPostScript() const override;
	virtual double width() const override;
	virtual double height() const override;
private:
	double _width, _height;
};


class Rectangle : public Shape
{
public:
	Rectangle(double width, double height);
	virtual std::string toPostScript() const override;
	virtual double width() const override;
	virtual double height() const override;
private:
	double _width, _height;
};


class Circle : public Shape
{
public:
	Circle(double radius);
	virtual std::string toPostScript() const override;
	virtual double width() const override;
	virtual double height() const override;
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
	virtual std::string toPostScript() const override;
	virtual double width() const override;
	virtual double height() const override;
private:
	std::vector<std::unique_ptr<Shape>> _shapes;
};
