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

// 计算两向量的夹角
double  AngleBetween(const TVector3D& vec1, const TVector3D& vec2);
// 计算两向量差的模
double  DistOf(const TPoint3D& lpt, const TPoint3D& rpt);
// 判断两向量是否平行
bool    IsParallel(const TVector3D& vec1, const TVector3D& vec2);
// 判断两向量是否垂直
bool    IsOrthogonal(const TVector3D& vec1, const TVector3D& vec2);
