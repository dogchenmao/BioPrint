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

// 设备是否已经连接
bool PrinterMachine::IsConnected(void)
{
	return m_MachineState != MS_OFFLINE
		&& m_MachineState != MS_CONNECTING;
	//&& ;//序列号要求
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

// 是否在轴复位中
bool PrinterMachine::IsHoming(void)
{
	return m_MachineState == MS_WAIT_HOMING;
}

// 是否在等待温度中
bool PrinterMachine::IsWaitTemp(void)
{
	return m_MachineState == MS_WAIT_TEMP;
}

// 是否在对高
bool PrinterMachine::IsZcheckManual(void)
{
	return m_MachineState == MS_WAIT_Z_CHECK_MANUAL;
}

// 是否在测平
bool PrinterMachine::IsLevelTest(void)
{
	return m_MachineState == MS_WAIT_LEVELTEST;
}

//// 传入：轴移动的距离    返回：软限位计算后，能够移动到的坐标点
//bool PrinterMachine::PosCalc(int nAxes, float Length, float& fValue, bool IsLimitZ)
//{
//	bool isZRevise = theApp.m_pref_Machine.m_isZRevise;
//	bool rValue = false;
//
//	//进行轴限位开关方向判断
//	if (nAxes == Z && isZRevise)
//	{
//		Length = -Length;
//	}
//
//	//fl 210131231,判断，手动对高时，不受下限控制
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
//	{//如果当前已经超出或等于尺寸极限，
//		if (Length <= 0)
//		{//如果继续超出，则不执行
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
//	{//如果当前已经超出或等于尺寸极限
//		if (Length >= 0)
//		{//如果继续超出，则不执行
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
//	{//否则设置为能支持的最大值
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
