#pragma once
#include "GlobleDefine.h"

class Point5D
{
public:
	Point5D();
	Point5D(Point5D& p);
	Point5D(double x, double y, double z);
	Point5D(double x, double y, double z, double _a, double _b);
	virtual ~Point5D();
	double operator[](const int nIndex);
	const Point5D& operator=(const Point5D&);

private:
	double values[5];
public:
	double  axis(int _axis);
	Point5D Get3D();
	void	setAxis(int _axis, double v);
	double	get(int idx);
	void	set(int idx, double v);
	void	set(double x, double y, double z);
	void	set(double x, double y, double z, double _a, double _b);
	// 获取每个点的X轴坐标
	double  Axis_X();
	// 获取每个点的Y轴坐标
	double  Axis_Y();
	// 获取每个点的Z轴坐标
	double  Axis_Z();
	double  Axis_A();						// 获取
	double  Axis_B();						// 获取
	// 设置每个点的X轴坐标
	void  setX(double x);
	// 设置每个点的Y轴坐标
	void  setY(double y);
	// 设置每个点的Z轴坐标
	void  setZ(double z);
	void  setA(double);						// 设置
	void  setB(double);						// 设置
	// 当前坐标加上输入坐标
	void  add(Point5D p1);
	// 当前坐标减去输入坐标
	void  sub(Point5D p1);
	// 两坐标点相减
	void  sub(Point5D p1, Point5D p2);
	// 两坐标点相除
	void  div(Point5D p1, Point5D p2);
	// 两坐标点相乘
	void  mul(Point5D p1, Point5D p2);
	// 坐标点四舍五入
	void  round();
	// 坐标点四舍五入, 并计算四舍五入时的误差
	void  round(Point5D& excess);
	// 计算坐标点的绝对值
	void  absolute();
	// 两坐标点的距离
	double  distance(Point5D p);
	// 坐标点到原点的距离
	double  length();
	// 坐标点到原点的距离
	double  magnitude();
	// 坐标点清零
	void remove();
};

