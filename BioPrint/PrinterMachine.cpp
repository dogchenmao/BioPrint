#pragma once
#include "PrinterMachine.h"

PrinterMachine::PrinterMachine()
{
	m_MachineState = MS_OFFLINE;
}


PrinterMachine::~PrinterMachine()
{
}

void PrinterMachine::SetMachineState(MachineState state)
{
	m_MachineState = state;
}

MachineState PrinterMachine::GetMachineState(void)
{
	return m_MachineState;
}

void PrinterMachine::SetMachinePos(Point5D& p)
{
	m_MachinePos.set(p.Axis_X(), p.Axis_Y(), p.Axis_Z(), p.Axis_A(), p.Axis_B());
}

void PrinterMachine::SetMachinePos(Point5D* p)
{
	m_MachinePos.set(p->Axis_X(), p->Axis_Y(), p->Axis_Z(), p->Axis_A(), p->Axis_B());
}

Point5D& PrinterMachine::GetMachinePos()
{
	return m_MachinePos;
}

bool PrinterMachine::IsNeedReset3dStartPos()
{
	return m_isNeedReset3dStartPos;
}

void PrinterMachine::SetNeedReset3dStartPos(bool isNeedReset)
{
	m_isNeedReset3dStartPos = isNeedReset;
}

bool PrinterMachine::IsConnecting(void)
{
	return m_MachineState == MS_CONNECTING;
}

// �豸�Ƿ��Ѿ�����
bool PrinterMachine::IsConnected(void)
{
	return m_MachineState != MS_OFFLINE
		&& m_MachineState != MS_CONNECTING;
	//&& ;//���к�Ҫ��
}


bool PrinterMachine::IsBuilding(void)
{
	return m_MachineState == MS_BUILDING || m_MachineState == MS_PAUSED;
}

bool PrinterMachine::IsPaused(void)
{
	return m_MachineState == MS_PAUSED;
}

bool PrinterMachine::IsReady(void)
{
	return m_MachineState == MS_READY;
}

// �Ƿ����Ḵλ��
bool PrinterMachine::IsHoming(void)
{
	return m_MachineState == MS_WAIT_HOMING;
}

// �Ƿ��ڵȴ��¶���
bool PrinterMachine::IsWaitTemp(void)
{
	return m_MachineState == MS_WAIT_TEMP;
}

// �Ƿ��ڶԸ�
bool PrinterMachine::IsZcheckManual(void)
{
	return m_MachineState == MS_WAIT_Z_CHECK_MANUAL;
}

// �Ƿ��ڲ�ƽ
bool PrinterMachine::IsLevelTest(void)
{
	return m_MachineState == MS_WAIT_LEVELTEST;
}

//// ���룺���ƶ��ľ���    ���أ�����λ������ܹ��ƶ����������
//bool PrinterMachine::PosCalc(int nAxes, float Length, float& fValue, bool IsLimitZ)
//{
//	bool isZRevise = theApp.m_pref_Machine.m_isZRevise;
//	bool rValue = false;
//
//	//��������λ���ط����ж�
//	if (nAxes == Z && isZRevise)
//	{
//		Length = -Length;
//	}
//
//	//fl 210131231,�жϣ��ֶ��Ը�ʱ���������޿���
//	if (!IsLimitZ)
//	{
//		if (Length > 0)
//		{
//			fValue = m_3DStartPos.get(nAxes) + Length;
//			rValue = true;
//			return rValue;
//		}
//		else
//		{
//			fValue = m_3DStartPos.get(nAxes) + Length;
//			if (fValue >= 0)
//			{
//				fValue = fValue;
//			}
//			else
//			{
//				fValue = 0;
//			}
//			rValue = true;
//			return rValue;
//		}
//	}
//
//	int isOut = isPosOutOfBuildSize(nAxes, m_3DStartPos.get(nAxes));
//	if (isOut == -1)
//	{//�����ǰ�Ѿ���������ڳߴ缫�ޣ�
//		if (Length <= 0)
//		{//���������������ִ��
//			fValue = m_3DStartPos.get(nAxes);
//			rValue = false;
//		}
//		else
//		{
//			fValue = m_3DStartPos.get(nAxes) + Length;
//			rValue = true;
//		}
//	}
//	else if (isOut == 1)
//	{//�����ǰ�Ѿ���������ڳߴ缫��
//		if (Length >= 0)
//		{//���������������ִ��
//			fValue = m_3DStartPos.get(nAxes);
//			rValue = false;
//		}
//		else
//		{
//			fValue = m_3DStartPos.get(nAxes) + Length;
//			rValue = true;
//		}
//	}
//	else if (isPosOutOfBuildSize(nAxes, m_3DStartPos.get(nAxes) + Length) == 0)
//	{//
//		fValue = m_3DStartPos.get(nAxes) + Length;
//		rValue = true;
//	}
//	else
//	{//��������Ϊ��֧�ֵ����ֵ
//		fValue = Length > 0 ? GetAxesBuildSize(nAxes) : .0;
//		rValue = true;
//	}
//
//	return rValue;
//}
//
//int PrinterMachine::isPosOutOfBuildSize(int nAxes, float pos)
//{
//	float BuildSize_X = theApp.m_pref_Machine.m_BuildSize_X;
//	float BuildSize_Y = theApp.m_pref_Machine.m_BuildSize_Y;
//	float BuildSize_Z = theApp.m_pref_Machine.m_BuildSize_Z;
//	int rValue = false;
//	switch (nAxes)
//	{
//	case X:
//		if (pos < 0)
//		{
//			rValue = -1;
//		}
//		else if (pos > BuildSize_X)
//		{
//			rValue = 1;
//		}
//		else
//		{
//			rValue = 0;
//		}
//		break;
//	case Y:
//		if (pos < 0)
//		{
//			rValue = -1;
//		}
//		else if (pos > BuildSize_Y)
//		{
//			rValue = 1;
//		}
//		else
//		{
//			rValue = 0;
//		}
//		break;
//	case Z:
//		if (pos < 0)
//		{
//			rValue = -1;
//		}
//		else if (pos > BuildSize_Z)
//		{
//			rValue = 1;
//		}
//		else
//		{
//			rValue = 0;
//		}
//		break;
//	}
//	return rValue;
//}
//
//float PrinterMachine::GetAxesBuildSize(int nAxes)
//{
//	switch (nAxes)
//	{
//	case X:
//		return theApp.m_pref_Machine.m_BuildSize_X;
//	case Y:
//		return theApp.m_pref_Machine.m_BuildSize_Y;
//	case Z:
//		return theApp.m_pref_Machine.m_BuildSize_Z;
//	}
//	return 0;
//}
