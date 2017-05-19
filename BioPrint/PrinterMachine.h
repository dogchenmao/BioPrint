#pragma once
#include "Point5D.h"
#include "GlobleDefine.h"

class PrinterMachine
{
public:
	PrinterMachine();
	~PrinterMachine();

	//设备实际坐标
	Point5D m_MachinePos;
	//设备当前状态
	MachineState m_MachineState;
	// 是否需要复位坐标
	bool m_isNeedReset3dStartPos;

public:
	// 设置设备状态
	void SetMachineState(MachineState state);
	// 获取设备状态
	MachineState GetMachineState(void);
	void SetMachinePos(Point5D& p);
	void SetMachinePos(Point5D* p);
	// 是否需要复位坐标
	bool IsNeedReset3dStartPos();
	// 设置是否需要复位坐标
	void SetNeedReset3dStartPos(bool isNeedReset);
	Point5D& GetMachinePos();
	// 判断是否正在连接设备
	bool IsConnecting(void);
	// 判断设备是否已连接
	bool IsConnected(void);
	// 判断设备是否正在打印
	bool IsBuilding(void);
	// 判断打印是否暂停
	bool IsPaused(void);
	// 判断是否正在对高
	bool IsZcheckManual(void);
	bool IsLevelTest(void);

	// 判断设备是否就绪
	bool IsReady(void);
	// 判断设备是否正在归零中
	bool IsHoming(void);
	// 判断是否在等待温度到达指定值
	bool IsWaitTemp(void);
	bool IsZCheck(void);			// 此函数未定义

	// 传入：轴移动的距离    返回：软限位计算后，能够移动到的坐标点
	bool PosCalc(int nAxes, float& Length, bool IsLimit);
	// 判断传入坐标是否在打印范围内
	int isPosOutOfBuildSize(int nAxes, float pos);
	// 获取对应轴最大打印尺寸
	float GetAxesBuildSize(int nAxes);
};

