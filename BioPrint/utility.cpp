//*****************************************************************************
//
//  utility.cpp:  Utility Implementation file
//
//*****************************************************************************
#include "utility.h"
#include "GeomBase.h"

// ******************************************************************
// �����������ļн�
//			 vec1 * vec2
//  cos�� = -------------
//			|vec1|*|vec2|
// ******************************************************************
double  AngleBetween(const TVector3D& vec1, const TVector3D& vec2)
{
	if (IsParallel(vec1, vec2))				// �ж��������Ƿ�ƽ��
	{// ������ƽ��, ���ؼн�Ϊ0
		return 0.0;
	}
	else
	{
		return acos(vec1*(vec2.GetNormal()) / vec1.Norm());
	}

}
// �ж��������Ƿ�ƽ��
bool  IsParallel(const TVector3D& vec1, const TVector3D& vec2)
{
	return IS_ZERO((vec1^vec2).Norm2());
}
// �������������ģ
double  DistOf(const TPoint3D& lpt, const TPoint3D& rpt)
{
	TVector3D vec = rpt - lpt;
	return vec.Norm();
}
// �ж��������Ƿ�ֱ
bool  IsOrthogonal(const TVector3D& vec1, const TVector3D& vec2)
{
	return IS_ZERO(vec1*vec2);
}