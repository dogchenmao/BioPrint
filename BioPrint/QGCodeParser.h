#pragma once
#include "Point5D.h"
#include "GlobleDefine.h"
#include <QObject>
struct G1Pick
{
	float fSource_X;	            // �ƶ�X�������
	float fSource_Y;				// �ƶ�Y�������
	float fSource_Z;				// �ƶ�Z�������
	float fSource_F;				// �ƶ��ٶ�
	bool isOldHas_X;                // �ж��Ƿ������ƶ�X��
	bool isOldHas_Y;				// �ж��Ƿ������ƶ�Y��
	bool isOldHas_Z;				// �ж��Ƿ������ƶ�Z��
	bool isOldHas_F;                // �жϵ�ǰ��ӡ�ٶ����ޱ仯
	G1Pick()
	{
		fSource_X = .0;
		fSource_Y = .0;
		fSource_Z = .0;
		fSource_F = .0;
		isOldHas_X = false;
		isOldHas_Y = false;
		isOldHas_Z = false;
		isOldHas_F = false;
	}
};
class QGCodeParser
{
public:
	QGCodeParser(void);
	~QGCodeParser(void);
private:
	Point5D m_CurrentPos;				// ��ǰλ��
	Point5D m_CurrentPos_Offset;
	int m_CurrentFeedRate;              // ��ǰ�ƶ��ٶ�(Ĭ��ֵΪ1200)
	bool isExtruderON;                  // �Ƿ���Ҫ��������
public:
	// ��G1ָ������ȡ����
	G1Pick& PickG1Value(G1Pick& valueRetern, QString& strSource);
	// ��G1ָ����д������Z����λ�����ڵײ�����Ը�ָ��ִ�У��г�-��ǰֵ
	QString& G1_CheckReviser(G1Pick& G1Values, QString& strDest);
	// ���㵱ǰG1ָ���ƶ������ʱ��
	double CalcG1Times(G1Pick& G1Values);
	// ���㵱ǰG1ָ���ƶ������ʱ��
	static double CalcG1Times(QString& strSource, Point5D& CurrentPos, int& CurrentFeedRate);
	// �ж��Ƿ���Ҫ��������
	bool IsExtruderON();
	// �Ƿ���G1ָ��
	bool IsG1(QString& strSource);
	// �Ƿ���M04ָ��
	bool IsM04(QString& strSource);
	// �Ƿ���M101ָ��
	bool IsM101(QString& strSource);
	// �Ƿ���M102ָ��
	bool IsM102(QString& strSource);
	// �Ƿ���M103ָ��
	bool IsM103(QString& strSource);
	// �Ƿ���M104ָ��
	bool IsM104(QString& strSource);
	// �Ƿ���M109ָ��
	bool IsM109(QString& strSource);
	// �Ƿ���M140ָ��
	bool IsM140(QString& strSource);
	// ��ȡ��ǰ����
	Point5D& GetCurrentPos();
	// ��ȡ��ǰ����
	Point5D& GetCurrentPos_Offset(Point5D& offset);

};


