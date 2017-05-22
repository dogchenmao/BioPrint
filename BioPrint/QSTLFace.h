#pragma once
#include "QSTLPoint.h"

class QSTLFace 
{

public:
	QSTLFace(void)
	{
		m_points[0] = m_points[1] = m_points[2] = -1;
		m_edges[0] = m_edges[1] = m_edges[2] = -1;
	}
	QSTLFace(const QSTLFace&);
	//operator
	const QSTLFace& operator= (const QSTLFace&);
	// Attributes
	QSTLPoint m_vector_normal;  //������
	int m_points[3];			//����		����Ӧ3�����㡿
	int m_edges[3];				//�߱��		����Ӧ3���ߡ�
};
