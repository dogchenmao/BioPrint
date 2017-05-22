#include "QSTLPoint.h"
#pragma region ���졢��������

QSTLPoint::QSTLPoint(void)
{
	m_dX = m_dY = m_dZ = 0.;
}

// ��������������ʼ������
QSTLPoint::QSTLPoint(float srcX, float srcY, float srcZ)
{
	m_dX = srcX;
	m_dY = srcY;
	m_dZ = srcZ;
}

// �Ե����ʼ������
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

// ���������ж�ȡ�����ݱ��浽��Ա������
void QSTLPoint::ReadSTLFile(istream& istream, STLFILETYPE stlFileType)
{
	m_dX = m_dY = m_dZ = .0f;                   // Ĭ�����õ�����Ϊ(0, 0, 0)

	char szTemp[25];
	if (stlFileType == ASCIISTLFILE)            // ASCII����ʽ��stl�ļ�
	{
		istream >> m_dX >> m_dY >> m_dZ;        // ��ȡһ��������(X,Y,Z)

		if (istream.fail())                     // �ж��Ƿ��ȡʧ��
		{
			istream.clear();                    // ���ʧ�ܱ�־

			for (int i = 0; i < 3; i++)			// ��ǰ����double�Ͷ�ȡʧ��, ���ٴ����ַ�����ʽ��ȡ��3������, ��ֹ�Ժ���ģ�����ݲ���Ӱ��
			{
				istream >> szTemp;
			}
		}

	}
	else
	{
		Q_ASSERT(stlFileType == BINSTLFILE);      // ����stl�ļ��Ƿ��Ƕ����Ƹ�ʽ(ǰ�����жϸ�stl�ļ�Ϊ��ASCII����ʽ)

		float tempVal;
		istream.read((char*)(&tempVal), sizeof (tempVal));          // ���������ж�ȡ4Byte����---->  X
		m_dX = (double)(tempVal);

		istream.read((char*)(&tempVal), sizeof (tempVal));          // ���������ж�ȡ4Byte����---->  Y
		m_dY = (double)(tempVal);

		istream.read((char*)(&tempVal), sizeof (tempVal));          // ���������ж�ȡ4Byte����---->  Z
		m_dZ = (double)(tempVal);
	}

	if (istream.bad())
	{
		QMessageBox::information(NULL, "ERROR", "STL file error!");
	}
}

// ���л�д����(�Զ����Ƹ�ʽд��)
void QSTLPoint::WriteArchive(QFile& archive)
{
	float tempVal = m_dX;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // д��X����

	tempVal = m_dY;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // д��Y����

	tempVal = m_dZ;
	archive.write((char*)(&tempVal), sizeof(tempVal));          // д��Z����
}


// �Ƚϵ������Ƿ����, Լ�����򷵻�0
bool QSTLPoint::isEqual(const QSTLPoint& secondPoint)
{
	double difference = 0.0;

	if (fabs(m_dZ - secondPoint.m_dZ) >= EPSINON)       difference = m_dZ - secondPoint.m_dZ;
	else if (fabs(m_dY - secondPoint.m_dY) >= EPSINON)  difference = m_dY - secondPoint.m_dY;
	else if (fabs(m_dX - secondPoint.m_dX) >= EPSINON)  difference = m_dX - secondPoint.m_dX;
	else                                                difference = 0;

	return difference == 0 ? true : false;
}

// ���õ������Ӧ��ķ���
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

// ��ȡ�������Ӧ��ķ���
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

// ���ӵ������Ӧ��ķ���
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

// ��ȡ�Ŵ��������Ӧ��ķ���
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

// �Ŵ�������Ӧ��ķ���
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
