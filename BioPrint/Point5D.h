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
	// ��ȡÿ�����X������
	double  Axis_X();
	// ��ȡÿ�����Y������
	double  Axis_Y();
	// ��ȡÿ�����Z������
	double  Axis_Z();
	double  Axis_A();						// ��ȡ
	double  Axis_B();						// ��ȡ
	// ����ÿ�����X������
	void  setX(double x);
	// ����ÿ�����Y������
	void  setY(double y);
	// ����ÿ�����Z������
	void  setZ(double z);
	void  setA(double);						// ����
	void  setB(double);						// ����
	// ��ǰ���������������
	void  add(Point5D p1);
	// ��ǰ�����ȥ��������
	void  sub(Point5D p1);
	// ����������
	void  sub(Point5D p1, Point5D p2);
	// ����������
	void  div(Point5D p1, Point5D p2);
	// ����������
	void  mul(Point5D p1, Point5D p2);
	// �������������
	void  round();
	// �������������, ��������������ʱ�����
	void  round(Point5D& excess);
	// ���������ľ���ֵ
	void  absolute();
	// �������ľ���
	double  distance(Point5D p);
	// ����㵽ԭ��ľ���
	double  length();
	// ����㵽ԭ��ľ���
	double  magnitude();
	// ���������
	void remove();
};

