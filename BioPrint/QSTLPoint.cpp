#include "QSTLPoint.h"
#pragma region 构造、析构函数

QSTLPoint::QSTLPoint(void)
{
	m_dX = m_dY = m_dZ = 0.;
}

// 以三个浮点数初始化点类
QSTLPoint::QSTLPoint(float srcX, float srcY, float srcZ)
{
	m_dX = srcX;
	m_dY = srcY;
	m_dZ = srcZ;
}

// 以点类初始化点类
QSTLPoint::QSTLPoint(const QSTLPoint& srcPoint)
{
	m_dX = srcPoint.m_dX;
	m_dY = srcPoint.m_dY;
	m_dZ = srcPoint.m_dZ;
}

QSTLPoint::~QSTLPoint(void)
{
}

#pragma endregion 

const QSTLPoint& QSTLPoint::operator=(const QSTLPoint& srcPoint)
{
	m_dX = srcPoint.m_dX;
	m_dY = srcPoint.m_dY;
	m_dZ = srcPoint.m_dZ;

	return *this;
}

// 从数据流中读取点数据保存到成员变量中
void QSTLPoint::ReadSTLFile(istream& istream, STLFILETYPE stlFileType)
{
	m_dX = m_dY = m_dZ = .0f;                   // 默认设置点坐标为(0, 0, 0)

	char szTemp[25];
	if (stlFileType == ASCIISTLFILE)            // ASCII码形式的stl文件
	{
		istream >> m_dX >> m_dY >> m_dZ;        // 获取一个点坐标(X,Y,Z)

		if (istream.fail())                     // 判断是否读取失败
		{
			istream.clear();                    // 清除失败标志

			for (int i = 0; i < 3; i++)			// 若前面以double型读取失败, 则再次以字符串形式读取这3个数据, 防止对后面模型数据产生影响
			{
				istream >> szTemp;
			}
		}

	}
	else
	{
		Q_ASSERT(stlFileType == BINSTLFILE);      // 断言stl文件是否是二进制格式(前面已判断该stl文件为非ASCII码形式)

		float tempVal;
		istream.read((char*)(&tempVal), sizeof (tempVal));          // 从输入流中读取4Byte数据---->  X
		m_dX = (double)(tempVal);

		istream.read((char*)(&tempVal), sizeof (tempVal));          // 从输入流中读取4Byte数据---->  Y
		m_dY = (double)(tempVal);

		istream.read((char*)(&tempVal), sizeof (tempVal));          // 从输入流中读取4Byte数据---->  Z
		m_dZ = (double)(tempVal);
	}

	if (istream.bad())
	{
		QMessageBox::information(NULL, "ERROR", "STL file error!");
	}
}

// 序列化写入流(以二进制格式写入)
void QSTLPoint::WriteArchive(QFile& archive)
{
	float tempVal = m_dX;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // 写入X坐标

	tempVal = m_dY;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // 写入Y坐标

	tempVal = m_dZ;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // 写入Z坐标
}


// 比较点坐标是否相等, 约等于则返回0
bool QSTLPoint::isEqual(const QSTLPoint& secondPoint)
{
	double difference = 0.0;

	if (fabs(m_dZ - secondPoint.m_dZ) >= EPSINON)       difference = m_dZ - secondPoint.m_dZ;
	else if (fabs(m_dY - secondPoint.m_dY) >= EPSINON)  difference = m_dY - secondPoint.m_dY;
	else if (fabs(m_dX - secondPoint.m_dX) >= EPSINON)  difference = m_dX - secondPoint.m_dX;
	else                                                difference = 0;

	return difference == 0 ? true : false;
}

// 设置点坐标对应轴的分量
void QSTLPoint::SetAxesValue(AxisId nAxes, float dfValue)
{
	switch (nAxes)
	{
	case 0:
		m_dX = dfValue;
		break;
	case 1:
		m_dY = dfValue;
		break;
	case 2:
		m_dZ = dfValue;
		break;
	}
}

// 获取点坐标对应轴的分量
float QSTLPoint::GetAxesValue(AxisId nAxes)
{
	double dfValue = .0f;

	switch (nAxes)
	{
	case 0:
		dfValue = m_dX;
		break;
	case 1:
		dfValue = m_dY;
		break;
	case 2:
		dfValue = m_dZ;
		break;
	}
	return dfValue;
}

// 增加点坐标对应轴的分量
void QSTLPoint::AddAxesValue(AxisId nAxes, float dfValue)
{
	switch (nAxes)
	{
	case 0:
		m_dX += dfValue;
		break;
	case 1:
		m_dY += dfValue;
		break;
	case 2:
		m_dZ += dfValue;
		break;
	}
}

// 获取放大后点坐标对应轴的分量
float QSTLPoint::GetMultiAxesValue(AxisId nAxes, float dfValue)
{
	double rValue = .0;
	switch (nAxes)
	{
	case 0:
		rValue = m_dX * dfValue;
		break;
	case 1:
		rValue = m_dY * dfValue;
		break;
	case 2:
		rValue = m_dZ * dfValue;
		break;
	}
	return rValue;
}

// 放大点坐标对应轴的分量
float QSTLPoint::MultiAxesValue(AxisId nAxes, float dfValue)
{
	float rValue = .0;
	switch (nAxes)
	{
	case 0:
		m_dX = rValue = m_dX * dfValue;
		break;
	case 1:
		m_dY = rValue = m_dY * dfValue;
		break;
	case 2:
		m_dZ = rValue = m_dZ * dfValue;
		break;
	}
	return rValue;
}
