#pragma once
#include "Point5D.h"
#include "GlobleDefine.h"

class PrinterMachine
{
public:
	PrinterMachine();
	~PrinterMachine();

	//�豸ʵ������
	Point5D m_MachinePos;
	//�豸��ǰ״̬
	MachineState m_MachineState;
	// �Ƿ���Ҫ��λ����
	bool m_isNeedReset3dStartPos;

public:
	// �����豸״̬
	void SetMachineState(MachineState state);
	// ��ȡ�豸״̬
	MachineState GetMachineState(void);
	void SetMachinePos(Point5D& p);
	void SetMachinePos(Point5D* p);
	// �Ƿ���Ҫ��λ����
	bool IsNeedReset3dStartPos();
	// �����Ƿ���Ҫ��λ����
	void SetNeedReset3dStartPos(bool isNeedReset);
	Point5D& GetMachinePos();
	// �ж��Ƿ����������豸
	bool IsConnecting(void);
	// �ж��豸�Ƿ�������
	bool IsConnected(void);
	// �ж��豸�Ƿ����ڴ�ӡ
	bool IsBuilding(void);
	// �жϴ�ӡ�Ƿ���ͣ
	bool IsPaused(void);
	// �ж��Ƿ����ڶԸ�
	bool IsZcheckManual(void);
	bool IsLevelTest(void);

	// �ж��豸�Ƿ����
	bool IsReady(void);
	// �ж��豸�Ƿ����ڹ�����
	bool IsHoming(void);
	// �ж��Ƿ��ڵȴ��¶ȵ���ָ��ֵ
	bool IsWaitTemp(void);
	bool IsZCheck(void);			// �˺���δ����

	// ���룺���ƶ��ľ���    ���أ�����λ������ܹ��ƶ����������
	bool PosCalc(int nAxes, float& Length, bool IsLimit);
	// �жϴ��������Ƿ��ڴ�ӡ��Χ��
	int isPosOutOfBuildSize(int nAxes, float pos);
	// ��ȡ��Ӧ������ӡ�ߴ�
	float GetAxesBuildSize(int nAxes);
};

