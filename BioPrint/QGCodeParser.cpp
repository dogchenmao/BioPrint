#include "QGCodeParser.h"
#include "Functions.h"

QGCodeParser::QGCodeParser()
{
	m_CurrentFeedRate = 1200;
	isExtruderON = false;
}


QGCodeParser::~QGCodeParser()
{
}
// 从G1指令中提取数据
G1Pick& QGCodeParser::PickG1Value(G1Pick& valueRetern, QString& strSource)
{
	//TODO: insert return statement here
	//提取XYZ值
	char szCode = 0;
	float Value = .0f;
	int nCode = -1;
	int CodeCount = 0;
	char szValue[32] = { 0 };
	char szLine[256] = { 0 };
	char **words = NULL;

	int nLen = std::min(256, strSource.length());
	//宽字节转单字节

	wcstombs(szLine, reinterpret_cast<const wchar_t *>(strSource.utf16()), nLen);
	strSource.clear();

	int n = split(&words, szLine, ' ', '(');            // 统计每行字符串的个数(用空格分割开的为一个字符串)，并存储在word中
	for (int i = 0; i < n; i++)
	{
		strcpy_s(szValue, words[i]);
		sscanf(szValue, "%c%f", &szCode, &Value);
		switch (szCode)
		{
		case 'X':
			if (!valueRetern.isOldHas_X)                // 如果上一条指令也是移动X轴，则跳过这条指令
			{
				valueRetern.fSource_X = Value;
				valueRetern.isOldHas_X = true;;
			}
			break;
		case 'Y':
			if (!valueRetern.isOldHas_Y)
			{
				valueRetern.fSource_Y = Value;
				valueRetern.isOldHas_Y = true;;
			}
			break;
		case 'Z':
			if (!valueRetern.isOldHas_Z)
			{
				valueRetern.fSource_Z = Value;
				valueRetern.isOldHas_Z = true;;
			}
			break;
		case 'F':
			if (!valueRetern.isOldHas_F)
			{
				valueRetern.fSource_F = Value;
				valueRetern.isOldHas_F = true;;
			}
			break;
		}
		free(words[i]);			// 释放内存
	}
	free(words);				// 释放内存

	return valueRetern;
}


// 对G1指令进行处理，如果Z轴限位开关在底部，则对该指令执行：行程-当前值
QString& QGCodeParser::G1_CheckReviser(G1Pick& G1Values, QString& strDest)
{
	float fDest_X = .0;
	float fDest_Y = .0;
	float fDest_Z = .0;
	float fDest_F = .0;
	QString str;

	////各轴是否反向，执行计算
	//if (theApp.m_SystemConfig.m_isXRevise)
	//{
	//	//fDest_X = theApp.m_SystemConfig.m_fBuildSize_X - G1Values.fSource_X;
	//	fDest_X = -1 * G1Values.fSource_X + 2 * theApp.m_SystemConfig.m_PlatformCenter_Pos.X;
	//}
	//else
	//{
	//	fDest_X = G1Values.fSource_X;
	//}

	//if (theApp.m_SystemConfig.m_isYRevise)
	//{
	//	//fDest_Y = theApp.m_SystemConfig.m_fBuildSize_Y - G1Values.fSource_Y;
	//	fDest_Y = -1 * G1Values.fSource_Y + 2 * theApp.m_SystemConfig.m_PlatformCenter_Pos.Y;
	//}
	//else
	//{
	//	fDest_Y = G1Values.fSource_Y;
	//}

	//if (theApp.m_SystemConfig.m_isZRevise)
	//{
	//	fDest_Z = theApp.m_SystemConfig.m_fBuildSize_Z - G1Values.fSource_Z;
	//}
	//else
	//{
	//	fDest_Z = G1Values.fSource_Z;
	//}
	//fDest_F = G1Values.fSource_F;
	////重新生成G1指令
	//strDest = _T("G1");
	//if (G1Values.isOldHas_X)
	//{
	//	str.Format(_T(" X%.4f"), fDest_X);
	//	strDest += str;
	//}
	//if (G1Values.isOldHas_Y)
	//{
	//	str.Format(_T(" Y%.4f"), fDest_Y);
	//	strDest += str;
	//}
	//if (G1Values.isOldHas_Z)
	//{
	//	str.Format(_T(" Z%.4f"), fDest_Z);
	//	strDest += str;
	//}
	//if (G1Values.isOldHas_F)
	//{
	//	str.Format(_T(" F%.4f"), fDest_F);
	//	strDest += str;
	//}
	return strDest;
}

// 计算当前G1指令移动所需的时间
double QGCodeParser::CalcG1Times(G1Pick& G1Values)
{
	double fTimes = 0;
	Point5D pOldPos = m_CurrentPos;

	if (G1Values.isOldHas_X)
	{
		//当前位置已变更
		m_CurrentPos.setX(G1Values.fSource_X);
	}
	if (G1Values.isOldHas_Y)
	{
		//当前位置已变更
		m_CurrentPos.setY(G1Values.fSource_Y);
	}
	if (G1Values.isOldHas_Z)
	{
		//当前位置已变更
		m_CurrentPos.setZ(G1Values.fSource_Z);
	}
	if (G1Values.isOldHas_F)
	{
		//当前速度已变更
		m_CurrentFeedRate = G1Values.fSource_F;
	}
	//时间计算
	if (m_CurrentFeedRate != 0)
	{
		fTimes = pOldPos.distance(m_CurrentPos) / m_CurrentFeedRate;
	}
	return fTimes;
}

// 计算当前G1指令移动所需的时间
double QGCodeParser::CalcG1Times(QString& strSource, Point5D& CurrentPos, int& CurrentFeedRate)
{
	double fTimes = 0;
	//G1指令判断
	if (strSource.length() <= 1 || strSource.at(0) != 'G' || strSource.at(1) != '1')
	{
		return fTimes;
	}

	//TODO: insert return statement here
	float fSource_X = .0;
	float fSource_Y = .0;
	float fSource_Z = .0;
	float fSource_F = .0;
	bool isOldHas_X = false;
	bool isOldHas_Y = false;
	bool isOldHas_Z = false;
	bool isOldHas_F = false;
	QString str;
	Point5D pOldPos = CurrentPos;
	//提取XYZ值
	char szCode = 0;
	float Value = .0f;
	int nCode = -1;
	int CodeCount = 0;
	char szValue[32] = { 0 };
	char szLine[256] = { 0 };
	char **words = NULL;

	int nLen = std::min(256, strSource.length());
	wcstombs(szLine, reinterpret_cast<const wchar_t *>(strSource.utf16()), nLen);
	strSource.clear();

	int n = split(&words, szLine, ' ', '(');
	for (int i = 0; i < n; i++)
	{
		strcpy_s(szValue, words[i]);
		sscanf(szValue, "%c%f", &szCode, &Value);
		switch (szCode)
		{
		case 'X':
			if (!isOldHas_X)
			{
				fSource_X = Value;
				isOldHas_X = true;;
			}
			break;
		case 'Y':
			if (!isOldHas_Y)
			{
				fSource_Y = Value;
				isOldHas_Y = true;;
			}
			break;
		case 'Z':
			if (!isOldHas_Z)
			{
				fSource_Z = Value;
				isOldHas_Z = true;;
			}
			break;
		case 'F':
			if (!isOldHas_F)
			{
				fSource_F = Value;
				isOldHas_F = true;;
			}
			break;
		}
		free(words[i]);
	}
	free(words);

	if (isOldHas_X)
	{
		//当前位置已变更
		CurrentPos.setX(fSource_X);
	}
	if (isOldHas_Y)
	{
		//当前位置已变更
		CurrentPos.setY(fSource_Y);
	}
	if (isOldHas_Z)
	{
		//当前位置已变更
		CurrentPos.setZ(fSource_Z);
	}
	if (isOldHas_F)
	{
		//当前速度已变更
		CurrentFeedRate = fSource_F;
	}
	//时间计算
	if (CurrentFeedRate != 0)
	{
		fTimes = pOldPos.distance(CurrentPos) / CurrentFeedRate;
	}
	return fTimes;
}


// 是否是G1指令
bool QGCodeParser::IsG1(QString& strSource)
{
	//G1指令判断
	if (strSource.length() <= 1 || strSource.at(0) != 'G' || strSource.at(1) != '1')
	{
		return false;
	}
	return true;
}


// 是否是M04指令
bool QGCodeParser::IsM04(QString& strSource)
{
	//G1指令判断
	if (strSource.length() <= 2 || strSource.at(0) != 'M' || strSource.at(1) != '0' || strSource.at(2) != '4')
	{
		return false;
	}
	return true;
}

// 是否是M101指令
bool QGCodeParser::IsM101(QString& strSource)
{
	//M101指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '1')
	{
		return false;
	}
	isExtruderON = true;
	return true;
}


// 是否是M102指令
bool QGCodeParser::IsM102(QString& strSource)
{
	//M101指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '2')
	{
		return false;
	}

	return true;
}


// 是否是M103指令
bool QGCodeParser::IsM103(QString& strSource)
{
	//G1指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '3')
	{
		return false;
	}
	isExtruderON = false;
	return true;
}

// 是否是M104指令
bool QGCodeParser::IsM104(QString& strSource)
{
	//M101指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '4')
	{
		return false;
	}

	return true;
}


// 是否是M109指令
bool QGCodeParser::IsM109(QString& strSource)
{
	//M101指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '9')
	{
		return false;
	}

	return true;
}


// 是否是M140指令
bool QGCodeParser::IsM140(QString& strSource)
{
	//M101指令判断
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '4' || strSource.at(3) != '0')
	{
		return false;
	}

	return true;
}



// 判断是否需要挤出材料
bool QGCodeParser::IsExtruderON()
{
	return isExtruderON;
}

// 获取当前坐标
Point5D& QGCodeParser::GetCurrentPos()
{
	return m_CurrentPos;
}

// 计算当前坐标和输入坐标的偏移(不清楚为什么需要通过返回值修改成员变量)
Point5D& QGCodeParser::GetCurrentPos_Offset(Point5D& offset)
{
	m_CurrentPos_Offset = m_CurrentPos;
	m_CurrentPos_Offset.sub(offset);
	return m_CurrentPos_Offset;
}

