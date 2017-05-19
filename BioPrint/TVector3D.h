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
	//  ��ֵ
	void SetValue(const double x, const double y, const double z);
	void SetValue(const TVector3D& vec3d);
	void SetValue(const double * vec3d);
	void SetValue(const TVector3D* vec3d);

	// ��������X����
	void x(const double x) { _x = x; }
	// ��������Y����
	void y(const double y) { _y = y; }
	// ��������Z����
	void z(const double z) { _z = z; }

	// ��ȡ����X����
	double x()const { return _x; }
	// ��ȡ����Y����
	double y()const { return _y; }
	// ��ȡ����Z����
	double z()const { return _z; }

public:
	// ������ģ
	double Norm() const;
	// ������ģ
	double Norm2() const;

	// ���ع�һ��������(���ı�ԭ����)
	TVector3D GetNormal() const;
	// ������һ��(�ı�ԭ����)
	void Normalize();

	// �ж��Ƿ�Ϊ������
	bool IsZero()const;

	// ��������XY������ģ
	double LengthXY() const;
	// ��������YZ������ģ
	double LengthYZ() const;
	// ��������XZ������ģ
	double LengthXZ() const;

public:
	// ��������� 
	TVector3D operator+(const TVector3D& vec3d)const;
	TVector3D operator-(const TVector3D& vec3d)const;
	double operator*(const TVector3D& vec3d)const;
	// �ж��������Ƿ�ƽ��
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
	// Debug ������
	void Trace();

private:
	double _x;
	double _y;
	double _z;
};
