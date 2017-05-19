#include "QModel.h"


QModel::QModel(void)
{
	m_StlSolid.Clear();
	//m_GCodeSolid = srcFace.m_GCodeSolid;
	m_hNotifyWnd = NULL;
}


QModel::~QModel(void)
{
}


QModel::QModel(const QModel& srQModel)
{
	m_StlSolid = srQModel.m_StlSolid;
	//m_GCodeSolid = srQModel.m_GCodeSolid;
	m_hNotifyWnd = srQModel.m_hNotifyWnd;
}


const QModel& QModel::operator=(const QModel& srQModel)
{
	m_StlSolid = srQModel.m_StlSolid;
	//m_GCodeSolid = srQModel.m_GCodeSolid;
	m_hNotifyWnd = srQModel.m_hNotifyWnd;

	return *this;
}
