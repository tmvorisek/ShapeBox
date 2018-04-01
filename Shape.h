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

class Square: public Rectangle
{
	Square(double length);
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
	double _width, _height;
};

class Horizontal : public Shape
{
public:
	Horizontal(std::vector<std::unique_ptr<Shape>> shapes);
	virtual std::string toPostScript() const override;
	virtual double width() const override;
	virtual double height() const override;
private:
	std::vector<std::unique_ptr<Shape>> _shapes;
	double _width, _height;
};

class Scale : public Shape
{
public:
	Scale(std::unique_ptr<Shape> shape, double fx, double fy);
	//virtual std::string toPostScript() override;
private:
	std::unique_ptr<Shape> _shape;
	double _fx, _fy;
};

//if angle != 90, 180 or 270 we default to 0
class Rotate : public Shape
{
public:
	Rotate(std::unique_ptr<Shape> shape, int angle);
	virtual double width() const override;
	virtual double height() const override;
	virtual std::string toPostScript() const override;
	int angle() const;

private:
	std::unique_ptr<Shape> _shape;
	double _width, _height;
	int _angle;
};