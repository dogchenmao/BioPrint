//*****************************************************************************
//
//  GeomBase.cpp:  GeomBase Implementation file
//
//*****************************************************************************

#include <QDebug>
#include "GeomBase.h"
#include "TVector3D.h"
#include <math.h>

#pragma region TPoint3D类
//////////   TPoint3D class implementation  ///////////////////////////////////

//*****************************************************************************
// TPoint3D: methods
//*****************************************************************************
void TPoint3D::SetValue(const double x, const double y, const double z)
{
	_x = x;
	_y = y;
	_z = z;
}
void TPoint3D::SetValue(const double* pt)
{
	_x = pt[0];
	_y = pt[1];
	_z = pt[2];
}
void TPoint3D::SetValue(const TPoint3D *pPt)
{
	SetValue(pPt->x(), pPt->y(), pPt->z());
}
void TPoint3D::SetValue(const TPoint3D& pt)
{
	SetValue(pt.x(), pt.y(), pt.z());
}

//*****************************************************************************
// TPoint3D: operators          运算符重载
//*****************************************************************************

TPoint3D& TPoint3D::operator =(const TPoint3D& rpt)
{
	_x = rpt.x();
	_y = rpt.y();
	_z = rpt.z();

	return *this;
}

bool TPoint3D::operator ==(const TPoint3D& rpt)
{
	return (IS_ZERO(_x - rpt.x()) && IS_ZERO(_y - rpt.y()) && IS_ZERO(_z - rpt.z()));
}

bool TPoint3D::operator !=(const TPoint3D& rpt)
{
	return !(*this == rpt);
}

TPoint3D& TPoint3D::operator +=(const TVector3D& vec)
{
	this->_x += vec.x();
	this->_y += vec.y();
	this->_z += vec.z();

	return *this;
}

TPoint3D TPoint3D::operator +(const TVector3D& vec) const
{
	return (TPoint3D(*this) += vec);
}

TPoint3D& TPoint3D::operator -=(const TVector3D& vec)
{
	this->_x -= vec.x();
	this->_y -= vec.y();
	this->_z -= vec.z();
	return *this;
}

TPoint3D TPoint3D::operator -(const TVector3D& vec) const
{
	return (TPoint3D(*this) -= vec);
}

TVector3D TPoint3D::operator -(const TPoint3D& rpt) const
{
	return TVector3D(_x - rpt.x(), _y - rpt.y(), _z - rpt.z());
}

//*****************************************************************************
// TPoint3D:: Trace() -- Debug 测试用
//*****************************************************************************
void TPoint3D::Trace()
{
	qDebug("\n");
	qDebug("** TPoint3D **\n");
	qDebug("Address   : %x\n", this);
	qDebug("Value     : ( %f\t%f\t%f\t)\n", this->x(), this->y(), this->z());
	qDebug("** End **\n");
}

//////  end TPoint    /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma endregion



#pragma region TMatrix3D类
//*****************************************************************************
//  TMatrix3D class Implementation
//*****************************************************************************
// constructor and destructor
TMatrix3D::TMatrix3D()
{
	Reset();
}

TMatrix3D::TMatrix3D(const TMatrix3D& matrix)
{
	SetValue(matrix);
}
TMatrix3D::TMatrix3D(const TMatrix3D* matrix)
{
	SetValue(matrix);
}
TMatrix3D::TMatrix3D(const double* matrix)
{
	SetValue(matrix);
}

//*****************************************************************************
// TMatrix3D:  methods
//*****************************************************************************

// 初始化矩阵为单位阵
void TMatrix3D::Reset()
{
	int row = 0;
	int col = 0;
	for (row = 0; row < 4; ++row)
	{
		for (col = 0; col < 4; ++col)
		{
			(*this)(row, col) = (row == col) ? 1.0 : 0.0;
		}
	}
}

void TMatrix3D::SetValue(const TMatrix3D* matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			_matrix[row * col + col] = (*matrix)(row, col);
		}
	}
}
void TMatrix3D::SetValue(const TMatrix3D& matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			_matrix[row * col + col] = matrix(row, col);
		}
	}
}
void TMatrix3D::SetValue(const double* matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			(*this)(row, col) = matrix[row * 4 + col];
		}
	}
}
//*****************************************************************************
// TMatrix3D: operators
//*****************************************************************************

double& TMatrix3D::operator ()(const int row, const int col)
{
	return _matrix[row * 4 + col];
}
double TMatrix3D::operator ()(const int row, const int col) const
{
	return _matrix[row * 4 + col];
}
TMatrix3D& TMatrix3D::operator =(const TMatrix3D& matrix)
{
	if (this != &matrix)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				(*this)(row, col) = matrix(row, col);
			}
		}
	}
	return *this;
}

TMatrix3D& TMatrix3D::operator +=(const TMatrix3D& matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			(*this)(row, col) += matrix(row, col);
		}
	}
	return *this;
}
TMatrix3D TMatrix3D::operator +(const TMatrix3D& matrix) const
{
	return (TMatrix3D(this) += matrix);
}

TMatrix3D& TMatrix3D::operator -=(const TMatrix3D& matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			(*this)(row, col) -= matrix(row, col);
		}
	}
	return *this;
}

TMatrix3D TMatrix3D::operator -(const TMatrix3D& matrix) const
{
	return (TMatrix3D(*this) -= matrix);
}

TMatrix3D TMatrix3D::operator *(const TMatrix3D& matrix) const
{
	TMatrix3D Mat;
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			Mat(row, col) = (*this)(row, 0) * matrix(0, col)
				+ (*this)(row, 1) * matrix(1, col)
				+ (*this)(row, 2) * matrix(2, col)
				+ (*this)(row, 3) * matrix(3, col);
		}
	}

	return Mat;
}

TMatrix3D& TMatrix3D::operator *=(const TMatrix3D& matrix)
{
	(*this) = (*this)*matrix;
	return *this;
}
#pragma endregion



//*****************************************************************************
// TMatrix3D: friends
//				[Xx, Yx, Zx, Tx]   [Vx]
//				[Xy, Yy, Zy, Ty]   [Vy]
//V' = M*T =	[Xz, Yz, Zz, Tz] * [Vz]
//				[0,  0,  0,  1 ]   [1 ]
//*****************************************************************************
TPoint3D operator*(const TMatrix3D& matrix, const TPoint3D& pt)
{
	double dx = 0.0;
	double dy = 0.0;
	double dz = 0.0;
	double dw = 0.0;

	dx = matrix(0, 0)*pt.x() + matrix(0, 1)*pt.y() + matrix(0, 2)*pt.z() + matrix(0, 3);
	dy = matrix(1, 0)*pt.x() + matrix(1, 1)*pt.y() + matrix(1, 2)*pt.z() + matrix(1, 3);
	dz = matrix(2, 0)*pt.x() + matrix(2, 1)*pt.y() + matrix(2, 2)*pt.z() + matrix(2, 3);
	dw = matrix(3, 0)*pt.x() + matrix(3, 1)*pt.y() + matrix(3, 2)*pt.z() + matrix(3, 3);
	return TPoint3D(dx / dw, dy / dw, dz / dw);
}
TVector3D operator*(const TMatrix3D& matrix, const TVector3D& vec)
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double w = 0.0;

	x = matrix(0, 0)*vec.x() + matrix(0, 1)*vec.y() + matrix(0, 2)*vec.z() + matrix(0, 3);
	y = matrix(1, 0)*vec.x() + matrix(1, 1)*vec.y() + matrix(1, 2)*vec.z() + matrix(1, 3);
	z = matrix(2, 0)*vec.x() + matrix(2, 1)*vec.y() + matrix(2, 2)*vec.z() + matrix(2, 3);
	w = matrix(3, 0)*vec.x() + matrix(3, 1)*vec.y() + matrix(3, 2)*vec.z() + matrix(3, 3);
	return TVector3D(x / w, y / w, z / w);
}
//*****************************************************************************
//  TMatrix3D:: Trace() -- Debug 测试用
//*****************************************************************************
void TMatrix3D::Trace()
{
	qDebug("\n");
	qDebug("** TMatrix3D **\n");
	qDebug("Address   : %x\n", this);
	qDebug("Value     : ( %f\t%f\t%f\t%f\t)\n", (*this)(0, 0), (*this)(0, 1), (*this)(0, 2), (*this)(0, 3));
	qDebug("          : ( %f\t%f\t%f\t%f\t)\n", (*this)(1, 0), (*this)(1, 1), (*this)(1, 2), (*this)(1, 3));
	qDebug("          : ( %f\t%f\t%f\t%f\t)\n", (*this)(2, 0), (*this)(2, 1), (*this)(2, 2), (*this)(2, 3));
	qDebug("          : ( %f\t%f\t%f\t%f\t)\n", (*this)(3, 0), (*this)(3, 1), (*this)(3, 2), (*this)(3, 3));
	qDebug("** End **\n");
}