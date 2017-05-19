//*****************************************************************************
//
//  utility.cpp:  Utility Implementation file
//
//*****************************************************************************
#include "utility.h"
#include "GeomBase.h"

// ******************************************************************
// 计算量向量的夹角
//			 vec1 * vec2
//  cosθ = -------------
//			|vec1|*|vec2|
// ******************************************************************
double  AngleBetween(const TVector3D& vec1, const TVector3D& vec2)
{
	if (IsParallel(vec1, vec2))				// 判断两向量是否平行
	{// 两向量平行, 返回夹角为0
		return 0.0;
	}
	else
	{
		return acos(vec1*(vec2.GetNormal()) / vec1.Norm());
	}

}
// 判断两向量是否平行
bool  IsParallel(const TVector3D& vec1, const TVector3D& vec2)
{
	return IS_ZERO((vec1^vec2).Norm2());
}
// 计算两向量差的模
double  DistOf(const TPoint3D& lpt, const TPoint3D& rpt)
{
	TVector3D vec = rpt - lpt;
	return vec.Norm();
}
// 判断两向量是否垂直
bool  IsOrthogonal(const TVector3D& vec1, const TVector3D& vec2)
{
	return IS_ZERO(vec1*vec2);
}