#include "Point5D.h"
#include <QtAlgorithms>

//三角类
Point5D::Point5D()
{
	values[0] = .0f;
	values[1] = .0f;
	values[2] = .0f;
	values[3] = .0f;
	values[4] = .0f;
}
double Point5D::operator[](const int nIndex)
{

	switch (nIndex)
	{
	case X:
		return values[0];
	case Y:
		return values[1];
	case Z:
		return values[2];
	case A:
		return values[3];
	case B:
		return values[4];
	default:
		return 0;
	}
	return 0;
}

const Point5D& Point5D::operator=(const Point5D& p)
{
	for (int i = 0; i < 5; i++)
	{
		values[i] = p.values[i];
	}
	return *this;
}

Point5D::~Point5D()
{

}

Point5D::Point5D(double x, double y, double z)
{
	values[0] = x; values[1] = y; values[2] = z;
	values[3] = .0f; values[4] = .0f;
}

Point5D::Point5D(double x, double y, double z, double _a, double _b)
{
	values[0] = x; values[1] = y; values[2] = z;
	values[3] = _a; values[4] = _b;
}
Point5D::Point5D(Point5D& p)
{
	values[0] = p.Axis_X();
	values[1] = p.Axis_Y();
	values[2] = p.Axis_Z();
	values[3] = p.Axis_A();
	values[4] = p.Axis_B();
}

// Getter/setter for by-AxisId access
double Point5D::axis(int _axis)
{
	return values[_axis];
}
void Point5D::setAxis(int _axis, double v)
{
	values[_axis] = v;
}

// Getter/setter for by-index access
double  Point5D::get(int idx)
{
	return values[idx];
}

void  Point5D::set(int idx, double v)
{
	values[idx] = v;
}
void Point5D::set(double x, double y, double z)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = .0f;
	values[4] = .0f;
}

void Point5D::set(double x, double y, double z, double _a, double _b)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = _a;
	values[4] = _b;
}

// Getters/setters for by-name access
double Point5D::Axis_X() { return values[0]; }
double Point5D::Axis_Y() { return values[1]; }
double Point5D::Axis_Z() { return values[2]; }
double Point5D::Axis_A() { return values[3]; }
double Point5D::Axis_B() { return values[4]; }
void Point5D::setX(double x) { values[0] = x; }
void Point5D::setY(double y) { values[1] = y; }
void Point5D::setZ(double z) { values[2] = z; }
void Point5D::setA(double _a) { values[3] = _a; }
void Point5D::setB(double _b) { values[4] = _b; }

void Point5D::add(Point5D p1)
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] += p1.values[idx];
	}
}

void Point5D::sub(Point5D p1)
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] -= p1.values[idx];
	}
}

void Point5D::sub(Point5D p1, Point5D p2)
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] = p1.values[idx] - p2.values[idx];
	}
}

/** Set the value of each element of this point to be the
* the value of the respective element of p1 divided by
* p2: this.value[axis] = p1.value[axis] / p2.value[axis].
* @param p1 numerator
* @param p2 denominator
*/
void Point5D::div(Point5D p1, Point5D p2)
{
	for (int idx = 0; idx < 5; idx++)
	{
		if (p2.values[idx] != 0)
		{
			values[idx] = p1.values[idx] / p2.values[idx];
		}
	}
}

/** Set the value of each element of this point to be the
* the value of the respective element of p1 multiplied by
* p2: this.value[axis] = p1.value[axis] * p2.value[axis].
* @param p1 multiplicand A
* @param p2 multiplicand B
*/
void Point5D::mul(Point5D p1, Point5D p2)
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] = p1.values[idx] * p2.values[idx];
	}
}

/**
* Round each element of the point to the nearest integer
* (using Math.round).
*/
void Point5D::round()      // 四舍五入
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] = floor(values[idx] + 0.5f);
	}
}

/**
* Round each element of the point to the nearest integer
* (using Math.round), storing the excess in the provided
* point object.
*/
void Point5D::round(Point5D& excess)
{
	double rounded = .0f;
	for (int idx = 0; idx < 5; idx++)
	{
		// 		if (excess.values[idx])
		// 		{
		rounded = floor(values[idx] + 0.5f);
		// 		} 
		// 		else
		// 		{
		// 			rounded = values[idx];
		// 		}
		excess.values[idx] = values[idx] - rounded;
		values[idx] = rounded;
	}
}

// 计算坐标点的绝对值
void Point5D::absolute()
{
	for (int idx = 0; idx < 5; idx++)
	{
		values[idx] = abs(values[idx]);
	}
}

Point5D Point5D::Get3D()
{
	Point5D p;
	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			p.values[i] = values[i];
		}
		else
		{
			p.values[i] = .0f;
		}
	}
	return p;
}

// 两坐标点的距离
double Point5D::distance(Point5D p)
{
	double acc = .0f;
	double delta = .0f;
	for (int idx = 0; idx < 5; idx++)
	{
		delta = values[idx] - p.values[idx];
		acc += (delta*delta);
	}
	return sqrt(acc);
}

// 坐标点到原点的距离
double Point5D::length()
{
	double acc = .0f;
	double delta = .0f;
	for (int idx = 0; idx < 5; idx++)
	{
		delta = values[idx];
		acc += (delta*delta);
	}
	return sqrt(acc);
}

// 坐标点到原点的距离
double Point5D::magnitude()
{
	double acc = .0f;
	double delta = .0f;
	for (int idx = 0; idx < 5; idx++)
	{
		delta = values[idx];
		acc += (delta*delta);
	}
	return sqrt(acc);
}

// 坐标点清零
void Point5D::remove()
{
	for (int i = 0; i < 5; i++)
	{
		values[i] = .0;
	}
}
