#pragma once
#include "Point5D.h"
#include "GlobleDefine.h"
#include <QObject>
struct G1Pick
{
	float fSource_X;	            // 移动X轴的坐标
	float fSource_Y;				// 移动Y轴的坐标
	float fSource_Z;				// 移动Z轴的坐标
	float fSource_F;				// 移动速度
	bool isOldHas_X;                // 判断是否正在移动X轴
	bool isOldHas_Y;				// 判断是否正在移动Y轴
	bool isOldHas_Z;				// 判断是否正在移动Z轴
	bool isOldHas_F;                // 判断当前打印速度有无变化
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
	Point5D m_CurrentPos;				// 当前位置
	Point5D m_CurrentPos_Offset;
	int m_CurrentFeedRate;              // 当前移动速度(默认值为1200)
	bool isExtruderON;                  // 是否需要挤出材料
public:
	// 从G1指令中提取数据
	G1Pick& PickG1Value(G1Pick& valueRetern, QString& strSource);
	// 对G1指令进行处理，如果Z轴限位开关在底部，则对该指令执行：行程-当前值
	QString& G1_CheckReviser(G1Pick& G1Values, QString& strDest);
	// 计算当前G1指令移动所需的时间
	double CalcG1Times(G1Pick& G1Values);
	// 计算当前G1指令移动所需的时间
	static double CalcG1Times(QString& strSource, Point5D& CurrentPos, int& CurrentFeedRate);
	// 判断是否需要挤出材料
	bool IsExtruderON();
	// 是否是G1指令
	bool IsG1(QString& strSource);
	// 是否是M04指令
	bool IsM04(QString& strSource);
	// 是否是M101指令
	bool IsM101(QString& strSource);
	// 是否是M102指令
	bool IsM102(QString& strSource);
	// 是否是M103指令
	bool IsM103(QString& strSource);
	// 是否是M104指令
	bool IsM104(QString& strSource);
	// 是否是M109指令
	bool IsM109(QString& strSource);
	// 是否是M140指令
	bool IsM140(QString& strSource);
	// 获取当前坐标
	Point5D& GetCurrentPos();
	// 获取当前坐标
	Point5D& GetCurrentPos_Offset(Point5D& offset);

};


