//*****************************************************************************
//  GeomBase.h 
//  Base Geometry class, TPoint: 3D point
//*****************************************************************************
// Author:  Liu Mingzeng    2009/11/27   DLUT  SAE Department
//
//*****************************************************************************
#pragma once

#include "utility.h"
#include <math.h>

class TMatrix3D;
class TVector3D;

//  Class Point3D
class TPoint3D
{
public:
	// 构造析构函数
	TPoint3D(double x = 0.0, double y = 0.0, double z = 0.0)
		:_x(x), _y(y), _z(z)
	{

	}
	TPoint3D(const TPoint3D& pt)
	{
		_x = pt._x;
		_y = pt._y;
		_z = pt._z;
	}
	TPoint3D(const TPoint3D* pt)
	{
		_x = pt->_x;
		_y = pt->_y;
		_z = pt->_z;
	}
	TPoint3D(const double* p)
	{
		SetValue(p);
	}
	virtual ~TPoint3D(){}

public:
	//  赋值
	void SetValue(const double x, const double y, const double z);
	void SetValue(const TPoint3D& pt);
	void SetValue(const TPoint3D *pPt);
	void SetValue(const double*);

	// 设置点坐标X分量
	void x(const double x){ _x = x; }
	// 设置点坐标Y分量
	void y(const double y){ _y = y; }
	// 设置点坐标Z分量
	void z(const double z){ _z = z; }

public:
	// 获取点坐标X分量
	double x()const { return _x; }
	// 获取点坐标Y分量
	double y()const { return _y; }
	// 获取点坐标Z分量
	double z()const { return _z; }

public:
	// 点与点的运算
	TPoint3D& operator=(const TPoint3D& rpt);
	bool operator==(const TPoint3D& rpt);
	bool operator!=(const TPoint3D& rpt);

	//// 点与矩阵相乘
	//friend	TPoint3D operator*(const TMatrix3D& matrix,const TPoint3D& point);

	// 点与向量的运算
	TPoint3D operator+(const TVector3D& vec3d)const;
	TPoint3D& operator+=(const TVector3D& vec3d);
	TPoint3D operator-(const TVector3D& vec3d)const;
	TPoint3D& operator-=(const TVector3D& vec3d);
	TVector3D operator-(const TPoint3D& pt)const;

public:
	// Debug 测试用
	void Trace();

private:
	double _x;
	double _y;
	double _z;
};

// Class Matrix3D 
class TMatrix3D
{
public:
	// 构造析构函数
	TMatrix3D();
	TMatrix3D(const TMatrix3D& matrix);
	TMatrix3D(const TMatrix3D* matrix);
	TMatrix3D(const double* matrix);
	virtual ~TMatrix3D(){}

public:
	// 重置为单位矩阵
	void Reset();
	void SetValue(const double* matrix);
	void SetValue(const TMatrix3D& matrix);
	void SetValue(const TMatrix3D* matrix);

	// 获取矩阵
	const double* GetMatrix() { return _matrix; }

public:
	// 操作符重载
	double& operator()(const int row, const int col);
	double operator()(const int row, const int col) const;
	TMatrix3D& operator=(const TMatrix3D& matrix);

	// 矩阵与 点 、向量的乘法
	friend	TPoint3D operator*(const TMatrix3D& matrix, const TPoint3D& point);
	friend  TVector3D operator*(const TMatrix3D& matrix, const TVector3D& vec3d);

	// 运算符重载
	TMatrix3D operator+(const TMatrix3D& matrix)const;
	TMatrix3D& operator+=(const TMatrix3D& matrix);
	TMatrix3D operator-(const TMatrix3D& matrix)const;
	TMatrix3D& operator-=(const TMatrix3D& matrix);
	TMatrix3D operator*(const TMatrix3D& matrix)const;
	TMatrix3D& operator*=(const TMatrix3D& matrix);

public:
	// Debug Edition 
	// 测试用
	void Trace();

private:
	double _matrix[16];
};
