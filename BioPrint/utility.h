//*****************************************************************************
//  utility.h 
//  common functions
//*****************************************************************************
// Author:  Liu Mingzeng    2009/11/27   DLUT  SAE Department
//
//*****************************************************************************
#pragma once

#include <math.h>
#include "TVector3D.h"
class TPoint3D;
class TVector3D;


const double  PI = 3.1415926535897932;
const double  ERR_VALUE = 1.0e-6;
#define       IS_ZERO(m_dX)  (fabs(m_dX) <= ERR_VALUE)

// �����������ļн�
double  AngleBetween(const TVector3D& vec1, const TVector3D& vec2);
// �������������ģ
double  DistOf(const TPoint3D& lpt, const TPoint3D& rpt);
// �ж��������Ƿ�ƽ��
bool    IsParallel(const TVector3D& vec1, const TVector3D& vec2);
// �ж��������Ƿ�ֱ
bool    IsOrthogonal(const TVector3D& vec1, const TVector3D& vec2);
