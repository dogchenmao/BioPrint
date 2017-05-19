#pragma once
#include "QSTLSolid.h"
#include "QGCodeSolid.h"
//////////////////////////////////////////////////////////////////////////
////	模型类。控制STL文件加载，GCode生成、加载。
//////////////////////////////////////////////////////////////////////////

class QModel
{
public:
	QModel(void);
	QModel(const QModel&);
	~QModel(void);
	const QModel& operator=(const QModel&);
private:
	QSTLSolid m_StlSolid;
	QGCodeSolid m_GCodeSolid;
	HWND m_hNotifyWnd;
public:
	// 获取stl模型
	inline QSTLSolid* GetSTLSolid() { return &m_StlSolid; }

	// 获取指向GCode模型数据指针
	inline QGCodeSolid* GetGCodeSolid() { return &m_GCodeSolid; }

	// 设置句柄
	inline void SetWnd(HWND hWnd)
	{
		m_hNotifyWnd = hWnd;
		m_StlSolid.SetWnd(hWnd);
		m_GCodeSolid.SetWnd(hWnd);
	}
};

