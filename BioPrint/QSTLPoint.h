#pragma once
#include "GlobleDefine.h"
#include <QFile>
#include <istream>
#include <QMessageBox>
using namespace std;

// stl模型点类(X, Y, Z)
class QSTLPoint
{
public:
	// 构造、析构函数
	QSTLPoint(void);
	QSTLPoint(float, float, float);
	QSTLPoint(const QSTLPoint&);
	~QSTLPoint(void);
public:
	// '='操作符重载
	const QSTLPoint& operator=(const QSTLPoint&);

	// 从STL文件读取流中取出一个点
	void ReadSTLFile(istream&, STLFILETYPE);

	// 写入点坐标数据
	void WriteArchive(QFile& archive);

	// 比较点,约等于则返回 0
	bool isEqual(const QSTLPoint&);

public:
	// 获取点坐标的x分量
	inline float X(void) { return m_dX; }

	// 获取点坐标的y分量
	inline float Y(void) { return m_dY; }

	// 获取点坐标的z分量
	inline float Z(void) { return m_dZ; }

	// 设置点坐标对应轴的分量
	void SetAxesValue(AxisId nAxes, float dfValue);

	// 获取点坐标对应轴的分量
	float GetAxesValue(AxisId nAxes);

	// 增加点坐标对应轴的分量
	void AddAxesValue(AxisId nAxes, float dfValue);

	// 获取放大后点坐标对应轴的分量
	float GetMultiAxesValue(AxisId nAxes, float dfValue);

	// 放大点坐标对应轴的分量
	float MultiAxesValue(AxisId nAxes, float dfValue);


private:
	float m_dX;            // 点坐标x分量
	float m_dY;            // 点坐标y分量
	float m_dZ;            // 点坐标z分量
};

