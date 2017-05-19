//*****************************************************************************
//
//  TVector3D.cpp:  TVector3D Implementation file
//
//*****************************************************************************

#include "TVector3D.h"
#include "utility.h"
#include <cmath>
#include <assert.h>
#include <QDebug>
#pragma region ���캯��
//*****************************************************************************
//  TVector3D:: constructors
//*****************************************************************************
TVector3D::TVector3D(const double x /* =0::0 */, const double y /* = 0::0 */,
	const double z /* = 0::0 */)
{
	SetValue(x, y, z);
}

TVector3D::TVector3D(const TVector3D& vec3d)
{
	SetValue(vec3d);
}
TVector3D::TVector3D(const double * vec3d)
{
	SetValue(vec3d);
}
TVector3D::TVector3D(const TVector3D* vec3d)
{
	SetValue(vec3d);
}
//*****************************************************************************
// TVector3D::methods I
//*****************************************************************************
void TVector3D::SetValue(const double x, const double y, const double z)
{
	_x = x;
	_y = y;
	_z = z;
}

void TVector3D::SetValue(const TVector3D* vec3d)
{
	SetValue(vec3d->x(), vec3d->y(), vec3d->z());
}

void TVector3D::SetValue(const TVector3D& vec3d)
{
	SetValue(vec3d.x(), vec3d.y(), vec3d.z());
}

void TVector3D::SetValue(const double * vec3d)
{
	SetValue(vec3d[0], vec3d[1], vec3d[2]);
}
#pragma endregion 

//*****************************************************************************
// TVector3D:: methods II       ������ģ
//*****************************************************************************
double TVector3D::Norm() const
{
	return Norm2();
}
// ������ģ
double TVector3D::Norm2() const
{
	return sqrt(_x*_x + _y*_y + _z*_z);
}
// ���ع�һ��������(���ı�ԭ����)
TVector3D TVector3D::GetNormal() const
{
	double norm = this->Norm2();
	if (IS_ZERO(norm))
	{
		return TVector3D();
	}
	else
	{
		double x = _x / norm;
		double y = _y / norm;
		double z = _z / norm;
		return TVector3D(x, y, z);
	}
}

// �ж��Ƿ�Ϊ������
bool TVector3D::IsZero() const
{
	return IS_ZERO(Norm2());
}

// ��������XY������ģ
double TVector3D::LengthXY() const
{
	return sqrt(_x*_x + _y*_y);
}
// ��������XZ������ģ
double TVector3D::LengthXZ() const
{
	return sqrt(_x*_x + _z*_z);
}
// ��������YZ������ģ
double TVector3D::LengthYZ() const
{
	return sqrt(_y*_y + _z*_z);
}
// ������һ��(�ı�ԭ����)
void TVector3D::Normalize()
{
	double norm = Norm2();
	assert(!IS_ZERO(norm));

	_x /= norm;
	_y /= norm;
	_z /= norm;
}

//*****************************************************************************
// TVector3D:: operators
//*****************************************************************************
TVector3D& TVector3D::operator=(const TVector3D& rhs)
{
	_x = rhs.x();
	_y = rhs.y();
	_z = rhs.z();
	return *this;
}

// equal
bool TVector3D::operator==(const TVector3D& vec3d) const
{
	// �о�����ֱ�Ӷ�double�ͱ����ж����������
	//return (this->x() == vec3d.x()) && (this->y() == vec3d.y())
	//	   && (this->z() == vec3d.z());

	return IS_ZERO((*this - vec3d).Norm2());
}

bool TVector3D::operator !=(const TVector3D& vec3d) const
{
	return !(*this == vec3d);
}


// dot product and cross product
double TVector3D::operator *(const TVector3D& vec3d) const
{
	return (_x * vec3d.x() + _y * vec3d.y() + _z * vec3d.z());
}

//*****************************************************************************
// �����ж��������Ƿ�ƽ��
// vec1 = {x1, y1, z1}				vec2 = {x2, y2, z2}
// 						x1	   y1     z1
//	��������ƽ��, ��   ---- = ---- = ----
//						x2     y2     z2
// ��
//		x1 * y2 - y1 * x2 = x1 * z2 - z1 * x2 = y1 * z2 - z1 * y2 = 0
//*****************************************************************************
TVector3D TVector3D::operator ^(const TVector3D& vec3d) const
{
	return TVector3D(_y * vec3d.z() - vec3d.y()* _z,
		vec3d.x() * _z - _x * vec3d.z(),
		_x * vec3d.y() - vec3d.x() * _y);
}

//  algorithm
TVector3D TVector3D::operator +(const TVector3D& vec3d) const
{
	return TVector3D(_x + vec3d.x(), _y + vec3d.y(), _z + vec3d.z());
}

TVector3D TVector3D::operator -(const TVector3D& vec3d) const
{
	return TVector3D(_x - vec3d.x(), _y - vec3d.y(), _z - vec3d.z());
}

TVector3D TVector3D::operator *(const double scale) const
{
	return TVector3D(_x * scale, _y * scale, _z * scale);
}

TVector3D TVector3D::operator/(const double scale) const
{
	return TVector3D(_x / scale, _y / scale, _z / scale);
}

TVector3D& TVector3D::operator +=(const TVector3D& vec3d)
{
	_x += vec3d.x();
	_y += vec3d.y();
	_z += vec3d.z();
	return *this;
}

TVector3D& TVector3D::operator -=(const TVector3D& vec3d)
{
	_x -= vec3d.x();
	_y -= vec3d.y();
	_z -= vec3d.z();
	return *this;
}

TVector3D& TVector3D::operator *=(const double scale)
{
	_x *= scale;
	_y *= scale;
	_z *= scale;
	return *this;
}

TVector3D& TVector3D::operator /=(const double scale)
{
	_x /= scale;
	_y /= scale;
	_z /= scale;
	return *this;
}

//*****************************************************************************
// TVector3D:: friends
//*****************************************************************************

TVector3D operator*(const double scale, const TVector3D& vec3d)
{
	return TVector3D(scale * vec3d.x(), scale * vec3d.y(), scale * vec3d.z());
}

//*****************************************************************************
// TVector3D:: Trace() -- ������
//*****************************************************************************
void TVector3D::Trace()
{
	qDebug("\n");
	qDebug("** TVector3D **\n");
	qDebug("Address   : %x\n", this);
	qDebug("Value     : ( %f\t%f\t%f\t)\n", this->x(), this->y(), this->z());
	qDebug("** End **\n");
}
