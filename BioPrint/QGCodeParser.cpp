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
// ��G1ָ������ȡ����
G1Pick& QGCodeParser::PickG1Value(G1Pick& valueRetern, QString& strSource)
{
	//TODO: insert return statement here
	//��ȡXYZֵ
	char szCode = 0;
	float Value = .0f;
	int nCode = -1;
	int CodeCount = 0;
	char szValue[32] = { 0 };
	char szLine[256] = { 0 };
	char **words = NULL;

	int nLen = std::min(256, strSource.length());
	//���ֽ�ת���ֽ�

	wcstombs(szLine, reinterpret_cast<const wchar_t *>(strSource.utf16()), nLen);
	strSource.clear();

	int n = split(&words, szLine, ' ', '(');            // ͳ��ÿ���ַ����ĸ���(�ÿո�ָ��Ϊһ���ַ���)�����洢��word��
	for (int i = 0; i < n; i++)
	{
		strcpy_s(szValue, words[i]);
		sscanf(szValue, "%c%f", &szCode, &Value);
		switch (szCode)
		{
		case 'X':
			if (!valueRetern.isOldHas_X)                // �����һ��ָ��Ҳ���ƶ�X�ᣬ����������ָ��
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
		free(words[i]);			// �ͷ��ڴ�
	}
	free(words);				// �ͷ��ڴ�

	return valueRetern;
}


// ��G1ָ����д������Z����λ�����ڵײ�����Ը�ָ��ִ�У��г�-��ǰֵ
QString& QGCodeParser::G1_CheckReviser(G1Pick& G1Values, QString& strDest)
{
	float fDest_X = .0;
	float fDest_Y = .0;
	float fDest_Z = .0;
	float fDest_F = .0;
	QString str;

	////�����Ƿ���ִ�м���
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
	////��������G1ָ��
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

// ���㵱ǰG1ָ���ƶ������ʱ��
double QGCodeParser::CalcG1Times(G1Pick& G1Values)
{
	double fTimes = 0;
	Point5D pOldPos = m_CurrentPos;

	if (G1Values.isOldHas_X)
	{
		//��ǰλ���ѱ��
		m_CurrentPos.setX(G1Values.fSource_X);
	}
	if (G1Values.isOldHas_Y)
	{
		//��ǰλ���ѱ��
		m_CurrentPos.setY(G1Values.fSource_Y);
	}
	if (G1Values.isOldHas_Z)
	{
		//��ǰλ���ѱ��
		m_CurrentPos.setZ(G1Values.fSource_Z);
	}
	if (G1Values.isOldHas_F)
	{
		//��ǰ�ٶ��ѱ��
		m_CurrentFeedRate = G1Values.fSource_F;
	}
	//ʱ�����
	if (m_CurrentFeedRate != 0)
	{
		fTimes = pOldPos.distance(m_CurrentPos) / m_CurrentFeedRate;
	}
	return fTimes;
}

// ���㵱ǰG1ָ���ƶ������ʱ��
double QGCodeParser::CalcG1Times(QString& strSource, Point5D& CurrentPos, int& CurrentFeedRate)
{
	double fTimes = 0;
	//G1ָ���ж�
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
	//��ȡXYZֵ
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
		//��ǰλ���ѱ��
		CurrentPos.setX(fSource_X);
	}
	if (isOldHas_Y)
	{
		//��ǰλ���ѱ��
		CurrentPos.setY(fSource_Y);
	}
	if (isOldHas_Z)
	{
		//��ǰλ���ѱ��
		CurrentPos.setZ(fSource_Z);
	}
	if (isOldHas_F)
	{
		//��ǰ�ٶ��ѱ��
		CurrentFeedRate = fSource_F;
	}
	//ʱ�����
	if (CurrentFeedRate != 0)
	{
		fTimes = pOldPos.distance(CurrentPos) / CurrentFeedRate;
	}
	return fTimes;
}


// �Ƿ���G1ָ��
bool QGCodeParser::IsG1(QString& strSource)
{
	//G1ָ���ж�
	if (strSource.length() <= 1 || strSource.at(0) != 'G' || strSource.at(1) != '1')
	{
		return false;
	}
	return true;
}


// �Ƿ���M04ָ��
bool QGCodeParser::IsM04(QString& strSource)
{
	//G1ָ���ж�
	if (strSource.length() <= 2 || strSource.at(0) != 'M' || strSource.at(1) != '0' || strSource.at(2) != '4')
	{
		return false;
	}
	return true;
}

// �Ƿ���M101ָ��
bool QGCodeParser::IsM101(QString& strSource)
{
	//M101ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '1')
	{
		return false;
	}
	isExtruderON = true;
	return true;
}


// �Ƿ���M102ָ��
bool QGCodeParser::IsM102(QString& strSource)
{
	//M101ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '2')
	{
		return false;
	}

	return true;
}


// �Ƿ���M103ָ��
bool QGCodeParser::IsM103(QString& strSource)
{
	//G1ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '3')
	{
		return false;
	}
	isExtruderON = false;
	return true;
}

// �Ƿ���M104ָ��
bool QGCodeParser::IsM104(QString& strSource)
{
	//M101ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '4')
	{
		return false;
	}

	return true;
}


// �Ƿ���M109ָ��
bool QGCodeParser::IsM109(QString& strSource)
{
	//M101ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '0' || strSource.at(3) != '9')
	{
		return false;
	}

	return true;
}


// �Ƿ���M140ָ��
bool QGCodeParser::IsM140(QString& strSource)
{
	//M101ָ���ж�
	if (strSource.length() <= 3 || strSource.at(0) != 'M' || strSource.at(1) != '1' || strSource.at(2) != '4' || strSource.at(3) != '0')
	{
		return false;
	}

	return true;
}



// �ж��Ƿ���Ҫ��������
bool QGCodeParser::IsExtruderON()
{
	return isExtruderON;
}

// ��ȡ��ǰ����
Point5D& QGCodeParser::GetCurrentPos()
{
	return m_CurrentPos;
}

// ���㵱ǰ��������������ƫ��(�����Ϊʲô��Ҫͨ������ֵ�޸ĳ�Ա����)
Point5D& QGCodeParser::GetCurrentPos_Offset(Point5D& offset)
{
	m_CurrentPos_Offset = m_CurrentPos;
	m_CurrentPos_Offset.sub(offset);
	return m_CurrentPos_Offset;
}

