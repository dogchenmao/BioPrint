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
	// ������������
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
	//  ��ֵ
	void SetValue(const double x, const double y, const double z);
	void SetValue(const TPoint3D& pt);
	void SetValue(const TPoint3D *pPt);
	void SetValue(const double*);

	// ���õ�����X����
	void x(const double x){ _x = x; }
	// ���õ�����Y����
	void y(const double y){ _y = y; }
	// ���õ�����Z����
	void z(const double z){ _z = z; }

public:
	// ��ȡ������X����
	double x()const { return _x; }
	// ��ȡ������Y����
	double y()const { return _y; }
	// ��ȡ������Z����
	double z()const { return _z; }

public:
	// ����������
	TPoint3D& operator=(const TPoint3D& rpt);
	bool operator==(const TPoint3D& rpt);
	bool operator!=(const TPoint3D& rpt);

	//// ����������
	//friend	TPoint3D operator*(const TMatrix3D& matrix,const TPoint3D& point);

	// ��������������
	TPoint3D operator+(const TVector3D& vec3d)const;
	TPoint3D& operator+=(const TVector3D& vec3d);
	TPoint3D operator-(const TVector3D& vec3d)const;
	TPoint3D& operator-=(const TVector3D& vec3d);
	TVector3D operator-(const TPoint3D& pt)const;

public:
	// Debug ������
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
	// ������������
	TMatrix3D();
	TMatrix3D(const TMatrix3D& matrix);
	TMatrix3D(const TMatrix3D* matrix);
	TMatrix3D(const double* matrix);
	virtual ~TMatrix3D(){}

public:
	// ����Ϊ��λ����
	void Reset();
	void SetValue(const double* matrix);
	void SetValue(const TMatrix3D& matrix);
	void SetValue(const TMatrix3D* matrix);

	// ��ȡ����
	const double* GetMatrix() { return _matrix; }

public:
	// ����������
	double& operator()(const int row, const int col);
	double operator()(const int row, const int col) const;
	TMatrix3D& operator=(const TMatrix3D& matrix);

	// ������ �� �������ĳ˷�
	friend	TPoint3D operator*(const TMatrix3D& matrix, const TPoint3D& point);
	friend  TVector3D operator*(const TMatrix3D& matrix, const TVector3D& vec3d);

	// ���������
	TMatrix3D operator+(const TMatrix3D& matrix)const;
	TMatrix3D& operator+=(const TMatrix3D& matrix);
	TMatrix3D operator-(const TMatrix3D& matrix)const;
	TMatrix3D& operator-=(const TMatrix3D& matrix);
	TMatrix3D operator*(const TMatrix3D& matrix)const;
	TMatrix3D& operator*=(const TMatrix3D& matrix);

public:
	// Debug Edition 
	// ������
	void Trace();

private:
	double _matrix[16];
};
