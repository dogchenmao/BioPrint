#pragma once
#include "GlobleDefine.h"
#include <QFile>
#include <istream>
#include <QMessageBox>
using namespace std;

// stlģ�͵���(X, Y, Z)
class QSTLPoint
{
public:
	// ���졢��������
	QSTLPoint(void);
	QSTLPoint(float, float, float);
	QSTLPoint(const QSTLPoint&);
	~QSTLPoint(void);
public:
	// '='����������
	const QSTLPoint& operator=(const QSTLPoint&);

	// ��STL�ļ���ȡ����ȡ��һ����
	void ReadSTLFile(istream&, STLFILETYPE);

	// д�����������
	void WriteArchive(QFile& archive);

	// �Ƚϵ�,Լ�����򷵻� 0
	bool isEqual(const QSTLPoint&);

public:
	// ��ȡ�������x����
	inline float X(void) { return m_dX; }

	// ��ȡ�������y����
	inline float Y(void) { return m_dY; }

	// ��ȡ�������z����
	inline float Z(void) { return m_dZ; }

	// ���õ������Ӧ��ķ���
	void SetAxesValue(AxisId nAxes, float dfValue);

	// ��ȡ�������Ӧ��ķ���
	float GetAxesValue(AxisId nAxes);

	// ���ӵ������Ӧ��ķ���
	void AddAxesValue(AxisId nAxes, float dfValue);

	// ��ȡ�Ŵ��������Ӧ��ķ���
	float GetMultiAxesValue(AxisId nAxes, float dfValue);

	// �Ŵ�������Ӧ��ķ���
	float MultiAxesValue(AxisId nAxes, float dfValue);


private:
	float m_dX;            // ������x����
	float m_dY;            // ������y����
	float m_dZ;            // ������z����
};

