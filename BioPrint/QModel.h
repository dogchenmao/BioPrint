#pragma once
#include "QSTLSolid.h"
#include "QGCodeSolid.h"
//////////////////////////////////////////////////////////////////////////
////	ģ���ࡣ����STL�ļ����أ�GCode���ɡ����ء�
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
	// ��ȡstlģ��
	inline QSTLSolid* GetSTLSolid() { return &m_StlSolid; }

	// ��ȡָ��GCodeģ������ָ��
	inline QGCodeSolid* GetGCodeSolid() { return &m_GCodeSolid; }

	// ���þ��
	inline void SetWnd(HWND hWnd)
	{
		m_hNotifyWnd = hWnd;
		m_StlSolid.SetWnd(hWnd);
		m_GCodeSolid.SetWnd(hWnd);
	}
};

