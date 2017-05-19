//*****************************************************************************
//  GeomBase.h 
//  Base Geometry class, TPoint: 3D point
//*****************************************************************************
// Author:  Liu Mingzeng    2009/11/27   DLUT  SAE Department
//
//*****************************************************************************
#pragma once

class TVector3D
{
public:
	TVector3D(const double x = 0.0, const double y = 0.0, const double z = 0.0);
	TVector3D(const double * veced);
	TVector3D(const TVector3D* vec3d);
	TVector3D(const TVector3D& vec3d);
	virtual ~TVector3D(){}


public:
	//  赋值
	void SetValue(const double x, const double y, const double z);
	void SetValue(const TVector3D& vec3d);
	void SetValue(const double * vec3d);
	void SetValue(const TVector3D* vec3d);

	// 设置向量X分量
	void x(const double x) { _x = x; }
	// 设置向量Y分量
	void y(const double y) { _y = y; }
	// 设置向量Z分量
	void z(const double z) { _z = z; }

	// 获取向量X分量
	double x()const { return _x; }
	// 获取向量Y分量
	double y()const { return _y; }
	// 获取向量Z分量
	double z()const { return _z; }

public:
	// 向量求模
	double Norm() const;
	// 向量求模
	double Norm2() const;

	// 返回归一化的向量(不改变原向量)
	TVector3D GetNormal() const;
	// 向量归一化(改变原向量)
	void Normalize();

	// 判断是否为零向量
	bool IsZero()const;

	// 计算向量XY分量的模
	double LengthXY() const;
	// 计算向量YZ分量的模
	double LengthYZ() const;
	// 计算向量XZ分量的模
	double LengthXZ() const;

public:
	// 运算符重载 
	TVector3D operator+(const TVector3D& vec3d)const;
	TVector3D operator-(const TVector3D& vec3d)const;
	double operator*(const TVector3D& vec3d)const;
	// 判断两向量是否平行
	TVector3D operator^(const TVector3D& vec3d)const;

	TVector3D operator*(const double scale)const;
	TVector3D operator/(const double scale)const;

	TVector3D& operator=(const TVector3D& rhs);

	TVector3D& operator+=(const TVector3D& vec3d);
	TVector3D& operator-=(const TVector3D& vec3d);


	TVector3D& operator*=(const double scale);
	TVector3D& operator/=(const double scale);

	bool operator==(const TVector3D& vec3d)const;
	bool operator!=(const TVector3D& vec3d)const;

	friend TVector3D operator*(const double scale, const TVector3D& vec3d);

public:
	// Debug 测试用
	void Trace();

private:
	double _x;
	double _y;
	double _z;
};
