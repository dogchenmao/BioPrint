#include "QSTLSolid.h"
#pragma region ���졢��������


QSTLSolid::QSTLSolid(QObject *parent)
: QThread(parent)
{
	Clear();
}

QSTLSolid::~QSTLSolid()
{
	//EndThread();        // ��������stlģ���߳�
	Clear();
}
const QSTLSolid& QSTLSolid::operator=(const QSTLSolid& srcSTLSolid)
{
	m_StlLoadState = srcSTLSolid.m_StlLoadState;
	m_strPathName_STL = srcSTLSolid.m_strPathName_STL;
	m_strPathName_GCode = srcSTLSolid.m_strPathName_GCode;
	m_fRunFlag = srcSTLSolid.m_fRunFlag;

	m_points = (srcSTLSolid.m_points);
	m_faces = (srcSTLSolid.m_faces);
	m_points_backup = (srcSTLSolid.m_points_backup);
	m_faces_backup = (srcSTLSolid.m_faces_backup);
	m_xMin = srcSTLSolid.m_xMin;
	m_xMax = srcSTLSolid.m_xMax;
	m_yMin = srcSTLSolid.m_yMin;
	m_yMax = srcSTLSolid.m_yMax;
	m_zMin = srcSTLSolid.m_zMin;
	m_zMax = srcSTLSolid.m_zMax;
	m_isModelChanged = srcSTLSolid.m_isModelChanged;

	return *this;
}

#pragma endregion 


// ���stlģ�Ͳ���
void QSTLSolid::Clear(void)
{
	m_xMin = 1000;
	m_yMin = 1000;                              // ��ʼ��ʱ����Сֵ���1000�������ֵ���-1000
	m_zMin = 1000;                              // Ϊ���ڽ������Ƚ���ʹʵ�ʵ����궼�ܱȳ�ʼʱ����Сֵ�󣬱����ֵС
	m_xMax = -1000;                             // �Ը���ʵ��stlģ�͵ĸ��������������С����
	m_yMax = -1000;
	m_zMax = -1000;

	m_fRunFlag = false;                         // ���ó�ʼ�߳�δ����
	m_isModelChanged = false;                   // ���ó�ʼģ��δ���޸�
	m_StlLoadState = STATE_STL_UNLOAD;          // ���ó�ʼģ��δ����
	m_points.clear();                       // ���stl���������
	m_faces.clear();                        // ���stl���������
}


// ��ȡģ�Ͷ�Ӧ������ļ�ֵ(isMin = trueΪ��ȡģ��λ�õ���Сֵ, isMin = falseΪ��ȡģ��λ�õ����ֵ)
float QSTLSolid::GetModelAxisPos(AxisId nAxes, bool isMin)
{
	float rValue = .0;
	if (isMin)
	{
		switch (nAxes)
		{
		case X:
			rValue = m_xMin;
			break;
		case Y:
			rValue = m_yMin;
			break;
		case Z:
			rValue = m_zMin;
			break;
		}
	}
	else
	{
		switch (nAxes)
		{
		case X:
			rValue = m_xMax;
			break;
		case Y:
			rValue = m_yMax;
			break;
		case Z:
			rValue = m_zMax;
			break;
		}
	}
	return rValue;
}

// ��ȡģ������ļ�ֵ(isMin = trueΪ��ȡģ��λ�õ���Сֵ, isMin = falseΪ��ȡģ��λ�õ����ֵ)
QSTLPoint QSTLSolid::GetModelPos(bool isMin)
{
	QSTLPoint stlPoint;

	if (isMin)
	{
		stlPoint = QSTLPoint(m_xMin, m_yMin, m_zMin);
	}
	else
	{
		stlPoint = QSTLPoint(m_xMax, m_yMax, m_zMax);
	}
	return stlPoint;
}


// ��ȡģ�ͳߴ�
QSTLPoint QSTLSolid::GetModelSize(void)
{
	float m_x = m_xMax - m_xMin;
	float m_y = m_yMax - m_yMin;
	float m_z = m_zMax - m_zMin;

	return QSTLPoint(m_x, m_y, m_z);
}


// ��ȡģ�����ĵ�����
QSTLPoint QSTLSolid::GetModelCenter(void)
{
	return m_Model_Center;
}


// ��ȡģ����ת�Ƕ�
QSTLPoint QSTLSolid::GetModelRotation(void)
{
	return m_fRotationValue;
}


// ���¼���ģ��ÿ����ĵ�λ������
void QSTLSolid::ReCalNormal(void)
{
	QSTLPoint PVertex[3];   // ������ʱ�洢stlģ��ÿ���������������
	int vertex_index;

	if (isStlLoaded())       // �ж�ģ���Ƿ��Ѽ���,ֻ����ģ���Ѿ������ص�����²��ܼ��㷨����
	{
		int totalFaces = m_faces.count();    // ��ȡstlģ������ĸ���
		for (int i = 0; i < totalFaces; i++)    // ����stlģ��ÿ����ķ�����
		{
			//ȡ��������
			for (int j = 0; j < 3; j++)
			{
				vertex_index = m_faces[i].m_points[j];
				PVertex[j] = m_points[vertex_index];
			}
			// ģ��ÿ����ķ���������(���㷽��Ϊ�������������)
			m_faces[i].m_vector_normal.SetAxesValue(X, (PVertex[0].Y() - PVertex[2].Y())*(PVertex[1].Z() - PVertex[2].Z()) - (PVertex[0].Z() - PVertex[2].Z())*(PVertex[1].Y() - PVertex[2].Y()));
			m_faces[i].m_vector_normal.SetAxesValue(Y, (PVertex[0].Z() - PVertex[2].Z())*(PVertex[1].X() - PVertex[2].X()) - (PVertex[1].Z() - PVertex[2].Z())*(PVertex[0].X() - PVertex[2].X()));
			m_faces[i].m_vector_normal.SetAxesValue(Z, (PVertex[0].X() - PVertex[2].X())*(PVertex[1].Y() - PVertex[2].Y()) - (PVertex[1].X() - PVertex[2].X())*(PVertex[0].Y() - PVertex[2].Y()));

			// �Է�������һ������
			float tt = m_faces[i].m_vector_normal.X() * m_faces[i].m_vector_normal.X()
				+ m_faces[i].m_vector_normal.Y() * m_faces[i].m_vector_normal.Y()
				+ m_faces[i].m_vector_normal.Z() * m_faces[i].m_vector_normal.Z();
			tt = pow(tt, 0.5);
			//���浥λ������
			m_faces[i].m_vector_normal.MultiAxesValue(X, 1.0 / tt);
			m_faces[i].m_vector_normal.MultiAxesValue(Y, 1.0 / tt);
			m_faces[i].m_vector_normal.MultiAxesValue(Z, 1.0 / tt);

		}
	}
}
//[����]		д����(�Ѷ����Ƹ�ʽ����stl�ļ�)
void QSTLSolid::WriteArchive(QFile& archive)
{
	unsigned short word = 0;
	char STLFileHead[80] = "Regenovo file";
	archive.write((char*)(STLFileHead), 80);                        // д��ǰ80�ֽ��ļ�ͷ

	int faceNum = m_faces.count();
	archive.write((char*)(&faceNum), sizeof(faceNum));

	for (int i = 0; i < faceNum; i++)
	{
		m_faces[i].m_vector_normal.WriteArchive(archive);               // д�����Ƭ�ķ�����

		for (int j = 0; j<3; j++)
		{
			m_points[m_faces[i].m_points[j]].WriteArchive(archive);     // д��3���������
		}

		//������
		archive.write((char*)(&word), sizeof(word));		        // д��������Ƭ��������Ϣ
	}
}

// ����stl�ļ�
void QSTLSolid::LoadSTL()
{
	//if (isStlLoadAble())                                                // �ж�stl�ļ��Ƿ����
	//{// stl�ļ��ɼ���
	//	if (IsThreadRunning())                                          // �жϼ���stl�߳��Ƿ�������(���Ƿ����ڼ���stl�ļ�)
	//	{// �����߳�������
	//		QString strInfo = _T("");
	//		//strInfo.LoadString(IDS_THREADRUNNING_LOADING_STL);
	//		if (AfxMessageBox(strInfo, MB_YESNO | MB_ICONSTOP) == IDYES)  // �����Ի�����ʾ
	//		{
	//			EndThread();
	//		}
	//		else
	//		{
	//			return;
	//		}
	//	}
	Clear();                    // �����µ�stl�ļ�ǰ�����stlģ�Ͳ���
	m_fRunFlag = true;				// ��Ϊ����Ҫ�����̲߳����У�����Ƚ��߳����б�־��Ϊtrue(���������ڷ���,��Ϊ�߳̿��ܴ���ʧ��)
	run();              // ��������stl�ļ��߳�
	//}
}
// �ж�stl�ļ��Ƿ���ASCII��ʽ
bool QSTLSolid::IsAsciiStlFile(ifstream& ifstream, long& filePtr)
{
	filePtr = 0;
	char buff[101];
	char* p = NULL;
	for (int i = 0; i < 20; i++)                    // ��ȡǰ20������,����������û��"FACET"�ַ���,���жϴ�stl�ļ�����ASCII����
	{
		if (ifstream.eof()) break;                  // �����ļ�����ֱ������

		ifstream.getline(buff, sizeof(buff)-1);   // ��ȡһ������(ÿ�����ȡ100������, ���1�ֽڴ��'\0')
		strcat_s(buff, "\0");                       // ���ַ���ĩβ���'\0'

		if (ifstream.bad())                         // �жϴ���Ĳ����Ƿ�������
		{
			return false;
		}
		_strupr_s(buff);                            // ���ַ���ȫ��ת���ɴ�д
		p = strstr(buff, "FACET");
		if (p != NULL)                              // ���ҵ�һ�γ���"FACET"��λ��(���ҵ��ַ���ֱ�ӷ���true����ʾ��stl�ļ�ΪASCII����)
		{
			return true;
		}
		filePtr = filePtr + strlen(buff);           // �����Ѷ�ȡ���ݵĳ���, ���ڷ���"FACET"�ַ�����λ��
	}

	return false;
}
// ��ȡASCII��ʽstl�ļ��ؼ���
bool QSTLSolid::ReadKeyword(istream& istream, const char* keyword)
{
	char buff[25];
	istream >> buff;
	if (istream.bad())
	{
		//"ReadKeyword��STL�ļ�����!"
		return false;
	}
	if (_strnicmp(buff, keyword, sizeof(buff)))				// �ж϶�ȡ����Ϣ�Ƿ�Ϊ�ؼ���,���Ƿ�Ϊkeyword
	{
		//"STL�ļ����д���, �Ƿ�ִֹͣ��Ӧ�ó���?λ�ڣ�"
		return false;
	}

	return true;
}

void QSTLSolid::run()
{
	unsigned long fileSize = 0;                             // stl�ļ���С
	unsigned long totalFaces = 0;                           // stlģ��������
	unsigned long pointCounter = 0;                         // stlģ�͵������ 
	unsigned long edgeCounter = 0;                          // stlģ�ͱ߼����� 
	unsigned long faceCounter = 0;                          // stlģ���������
	QSTLPoint point;                                // ��ʱ���stlģ�͵�������Ϣ
	QSTLFace face;                                  // ��ʱ���stlģ������Ϣ

	//***************************************************************/
	//**************************��ȡstl�ļ�**************************
	//***************************************************************/

	//SetCurrState(pThreadInfo, STATE_STL_LOADING);                       // ���õ�ǰ״̬Ϊstl�ļ�������...
	QString str = m_strPathName_STL;								 // ��ȡstl�ļ���
	ifstream inputFile(str.toStdString().c_str(), ios::in | ios::_Nocreate);				 // ��ֻ����ʽ��stl�ļ�
	str.clear();
	if (inputFile.bad())                                                // �ж��ļ��Ƿ�����
	{// �ļ�����
		goto LOAD_ERROR;
	}
	inputFile.seekg(0, ios::end);                                       // ��λ���ļ���β�����ڻ�ȡ�ļ�����

	if ((fileSize = inputFile.tellg()) == -1L)                          // �ж��Ƿ��ǿ��ļ�
	{// ���ļ�
		goto LOAD_ERROR;
	}
	inputFile.seekg(0, ios::beg);                                       // ���·����ļ�ͷ

	//***************************************************************/
	//**************************�ж�stl�ļ���ʽ**********************
	//****************************BINARY/ASCII***********************
	//***************************************************************/
	long filePtr;                                                       // ASCII����stl�ļ��ַ���"facet"��ƫ����
	STLFILETYPE fileType = NONSTLFILE;                                  // stl�ļ�����(��ʼ��Ϊ��stl�ļ�)

	if (IsAsciiStlFile(inputFile, filePtr))                             // �ж��ļ���ʽΪASCII���ͻ���BINARY����
	{// stl�ļ�ΪASCII����
		inputFile.seekg(filePtr, ios::beg);	                            // ��λ���ַ���"facet"��
		fileType = ASCIISTLFILE;				                        // ���ΪASCII�ļ�
	}
	else
	{// stl�ļ�ΪBINARY����
		inputFile.close();                                              // �ر��ļ�,�Ա���һ���Զ�������ʽ���ļ�
		inputFile.open(m_strPathName_STL.toStdString().c_str(), ios::in | ios::_Nocreate | ios::binary);     // �Զ�������ʽ��stl�ļ�
		inputFile.seekg(80, ios::beg);                                  // ����ǰ80�ֽ��ļ�ͷ

		if (fileSize < 134)                                             // һ������������STL�ļ�����Ϊ134�ֽ�(80+4+50)
		{
			goto LOAD_ERROR;
		}

		if (inputFile.bad())                                            // ���ɶ��ļ�
		{
			goto LOAD_ERROR;
		}

		inputFile.read((char*)(&totalFaces), sizeof (totalFaces));      // ȡ��stlģ��������(4 bytes)

		if (inputFile.bad())
		{
			goto LOAD_ERROR;
		}
		if (totalFaces <= 0)                                            // �ж�stlģ����Ƭ���Ƿ�С�ڻ������
		{// С�ڵ���0ֱ������
			goto LOAD_ERROR;
		}
		if (fileSize != 84 + totalFaces * 50)                           // �ļ���С������(84 + 50��������)
		{
			goto LOAD_ERROR;
		}
		fileType = BINSTLFILE;                                          // �������������������,����Ϊ��stl�ļ�Ϊ����������
	}

	//***************************************************************/
	//                           ��ȡstl�ļ�����
	//                    inputFile�Ѿ���λ�����ݲ���
	//***************************************************************/
	float fIterStep = 0;                            // 1%��stl�ļ���С,���ڽ�������ʾ
	int nOldStep = 0;                               // �˱��������жϵ�ǰ�Ľ��Ⱥ��ϴ�ִ�еĽ������޲���в��ʱ�����´˱�������ˢ�½�����

	if (fileType == ASCIISTLFILE)                   // stl�ļ�ΪASCII����
	{
		fIterStep = fileSize / 100.0;                                   // ���ļ��ܳ��ȷֳ�100�ݣ�������ʾ���ؽ���
		char buff[25];                                                  // ������ʱ��Ŵ��ļ��ж�ȡ������
		unsigned long  nPosition = 0;                                            // ��ǰ��ȡ���ļ����ݵ�λ��
		while (m_fRunFlag && nPosition < fileSize)
		{
			nPosition = inputFile.tellg();                              // ��ȡ��ǰ�Ѷ�ȡ�ļ�����
			int nTem = nPosition / fIterStep;                           // fIterStepΪ�ܳ��ȵ�1%��nPositionΪ�Ѷ�ȡ�ĳ��ȣ�����Ľ��nTemΪ��ȡ�ļ��İٷֱ�
			if (nOldStep != nTem)                                       // �жϵ�ǰ���صĽ��Ⱥ��ϴ����޲��
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);                          // ˢ�½�����
			}

			inputFile >> buff;

			// ����Ϊ��ASCII���͵�stl�ļ��Ľ���, ��Ҫ��stl�ļ���ʽ��һ���˽�
			// �����ȡ��ǰ���ݲ���"facet"���˳�(��Ϊ�����ѭ��ǰ�Ѿ����ļ�ָ�붨λ�����ַ���ǰ����)
			if (_strnicmp(buff, "facet", 5) != 0)
				break;
			// Read normal vector ��ȡ������
			if (!ReadKeyword(inputFile, "normal"))                      // �жϵ�ǰ�ַ����ǲ���"normal"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			point.ReadSTLFile(inputFile, fileType);                     // ��ȡƽ�淨����
			face.m_vector_normal = point;

			// Read three Points
			if (!ReadKeyword(inputFile, "outer"))                       // �жϵ�ǰ�ַ����ǲ���"outer"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			if (!ReadKeyword(inputFile, "loop"))                        // �жϵ�ǰ�ַ����ǲ���"loop"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			for (int i = 0; i<3; i++)                                   // ��ȡ������Ƭ������������
			{
				if (!ReadKeyword(inputFile, "vertex"))
				{
					inputFile.close();
					goto LOAD_ERROR;
				}

				point.ReadSTLFile(inputFile, fileType);                 // ��ȡ������
				m_points.append(point);                       // ��������ӵ�stl�ļ������������
				face.m_points[i] = pointCounter;                        // ����stlģ��ƽ���3�����������
				SetMinMaxVal(point.X(), m_xMin, m_xMax);
				SetMinMaxVal(point.Y(), m_yMin, m_yMax);        // ����ģ�ͳߴ�
				SetMinMaxVal(point.Z(), m_zMin, m_zMax);
				pointCounter++;
			}

			if (!ReadKeyword(inputFile, "endloop"))                     // �жϵ�ǰ�ַ����ǲ���"endloop"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			if (!ReadKeyword(inputFile, "endfacet"))                    // �жϵ�ǰ�ַ����ǲ���"endfacet"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}
			// ע: pThreadInfo->m_faces.Add(face); faceCounter++; <==> pThreadInfo->m_faces.SetAt(faceCounter++, face);
			m_faces.append(face);
			faceCounter++;

			//pThreadInfo->DoEvent();
		}
		if (!m_fRunFlag)                                   // �ж��߳��Ƿ�������
		{
			goto LOAD_ERROR;
		}
		totalFaces = faceCounter;

		// �ж�ASCII��ʽ��stl�ļ��Ƿ���"endfacet"�ַ�������
		if (_strnicmp(buff, "endsolid", sizeof(buff)) != 0)
		{
			inputFile.close();
			goto LOAD_ERROR;
		}

	}
	else if (fileType == BINSTLFILE)                // stl�ļ�ΪASCII����
	{
		// ��ȡ������stl�ļ�
		try
		{
			m_faces.resize(totalFaces);                   // ����stl�����д�С
			m_points.resize(totalFaces * 3);              // ����stl�����д�С
		}
		catch (QException*)
		{
			QMessageBox::information(NULL, "ERROR", "Memory allocation failure!");
			goto LOAD_ERROR;
		}


		////////////////////////////////////////////////////////////
		fIterStep = totalFaces / 100.0;                                 // ���ļ��ܳ��ȷֳ�100�ݣ�������ʾ���ؽ���

		for (unsigned long counter = 0; counter < totalFaces && m_fRunFlag; counter++)
		{
			if (inputFile.eof())                                        // �ݴ���, �ж��ļ��Ƿ��Ѷ���
			{
				if (counter + 1 != totalFaces)                          // �ļ��Ѿ�������,����������Ƭ����������totalFaces
				{
					QMessageBox::information(NULL, "ERROR", "Practical reading patch does not match!");
				}
				totalFaces = counter;
				m_faces.resize(totalFaces);               // ����stl�����д�С
				m_points.resize(totalFaces * 3);          // ����stl�����д�С
				break;
			}

			int nTem = faceCounter / fIterStep;                         // fIterStepΪ�ܳ��ȵ�1%��faceCounterΪ�Ѷ�ȡ�ĳ��ȣ�����Ľ��nTemΪ��ȡ�ļ��İٷֱ�
			if (nOldStep != nTem)                                       // �жϵ�ǰ���صĽ��Ⱥ��ϴ����޲��
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);                          // ���½�����
			}

			// ��ȡ������
			point.ReadSTLFile(inputFile, fileType);
			face.m_vector_normal = point;

			// ��ȡ������
			for (int i = 0; i < 3 && m_fRunFlag; i++)
			{
				point.ReadSTLFile(inputFile, fileType);
				m_points.replace(pointCounter, point);
				face.m_points[i] = pointCounter;
				SetMinMaxVal(point.X(), m_xMin, m_xMax);
				SetMinMaxVal(point.Y(), m_yMin, m_yMax);        // ����ģ�ͳߴ�
				SetMinMaxVal(point.Z(), m_zMin, m_zMax);
				pointCounter++;
			}

			m_faces.replace(faceCounter++, face);

			// ��ȡ�ļ�����
			unsigned short attribute;
			inputFile.read((char*)(&attribute), sizeof(attribute));

			if (inputFile.bad())
			{
				goto LOAD_ERROR;
			}
			//pThreadInfo->DoEvent();
		}
	}
	else
	{
		goto LOAD_ERROR;
	}
	if (!m_fRunFlag)                                       // �߳�δ����
	{
		goto LOAD_ERROR;
	}
	inputFile.close();                                                  // �ر��ļ�
	MovetoCenter();                                        // ��ģ���ƶ�������
	ModelBackUp();                                         // ����ģ������
	//SetCurrState(pThreadInfo, STATE_STL_LOADED);                        // ����stl�ļ�����״̬Ϊ"�Ѽ���"
	m_fRunFlag = false;                                    // ��stl�ļ����б�־��Ϊfalse, ����stl�ļ��Ѽ������

LOAD_ERROR:
	inputFile.close();                                                  // �ر��ļ�
	//SetCurrState(pThreadInfo, STATE_STL_LOADFAILED);                    // ����stl�ļ�����״̬Ϊ"����ʧ��"
	m_fRunFlag = false;                                    // ��stl�ļ����б�־��Ϊfalse, ����stl�ļ��Ѽ������
	//m_hThreadHandle = NULL;                                // ���stl�ļ������߳̾��
}

// ģ��ƽ��
void QSTLSolid::AxesMove(AxisId axes, float movedlength)
{
	unsigned long totalPointCount = m_points.count();        // ��ȡstlģ���е�ĸ���

	if (totalPointCount == 0)
	{
		return;
	}

	for (unsigned long i = 0; i < totalPointCount; i++)			// ����ƽ�ƺ�ģ�͵�����
	{
		m_points[i].AddAxesValue(axes, movedlength);
	}
	CalQModelSize();                                    // ���»�ȡstlģ�͵ĳߴ�
	m_isModelChanged = true;                            // ��ģ���Ѹ��Ĳ�����Ϊtrue��֪ͨӦ�ó�����Ҫ�ػ�ģ��
}
// ģ���ƶ���ƽ̨
void QSTLSolid::MovetoPlateform()
{
	if (abs(m_zMin) > 0)                                 // �ж�ģ���Ƿ��Ѿ���ƽ̨��
	{
		AxesMove(Z, -m_zMin);
	}
}
// ģ���ƶ�������(Z�ᱣ�ֲ���)
void QSTLSolid::MovetoCenter()
{
	double movevalue = .0f;
	movevalue = (m_xMax + m_xMin) / 2;                  // ��ȡģ�͵�ǰλ�����ĵ�X����
	if (abs(movevalue) > 1e-6)                          // �ж�ģ���Ƿ��Ѿ�������
	{
		AxesMove(X, -movevalue);
	}

	movevalue = (m_yMax + m_yMin) / 2;                  // ��ȡģ�͵�ǰλ�����ĵ�Y����
	if (abs(movevalue) > 1e-6)                          // �ж�ģ���Ƿ��Ѿ�������
	{
		AxesMove(Y, -movevalue);
	}
}

// ����������ʱ����תģ��
void QSTLSolid::OnRotation(AxisId axes, float fRotationValue)
{
	double xVal, yVal, zVal;
	double rotateAngle = fRotationValue * 3.1415926535898 / 180.0;              // ��ת���Ƕ�ת��Ϊ����

	unsigned long totalPoints = m_points.count();            // ��ȡstlģ���е�ĸ���

	m_fRotationValue.SetAxesValue(axes, (int)(m_fRotationValue.GetAxesValue(axes) + fRotationValue + 360) % 360);    // ���¶�Ӧ�����ת�Ƕ�

	if (totalPoints == 0)
	{
		return;
	}

	float X_Center = (m_xMin + m_xMax) / 2;
	float Y_Center = (m_yMin + m_yMax) / 2;
	float Z_Center = (m_zMin + m_zMax) / 2;
	float m_zMin_Last = m_zMin;                         // ��¼ģ��Z�᷽����С����, �Ա���ת��ģ�����ڴ�������

	for (unsigned long i = 0; i < totalPoints; i++)             // ��stlģ��ÿ�����������ת(��ʱ����ת��ʽΪ:x'=x*cos��-y*sin��   y'=x*sin��+cos��)
	{
		switch (axes)
		{
		case X:
			m_points[i].SetAxesValue(Y, m_points[i].Y() - Y_Center);
			m_points[i].SetAxesValue(Z, m_points[i].Z() - Z_Center);

			yVal = m_points[i].GetMultiAxesValue(Y, cos(rotateAngle))
				- m_points[i].GetMultiAxesValue(Z, sin(rotateAngle));
			zVal = m_points[i].GetMultiAxesValue(Y, sin(rotateAngle))
				+ m_points[i].GetMultiAxesValue(Z, cos(rotateAngle));

			m_points[i].SetAxesValue(Y, yVal + Y_Center);
			m_points[i].SetAxesValue(Z, zVal + Z_Center);

			break;
		case Y:
			m_points[i].SetAxesValue(X, m_points[i].X() - X_Center);
			m_points[i].SetAxesValue(Z, m_points[i].Z() - Z_Center);

			xVal = m_points[i].GetMultiAxesValue(X, cos(rotateAngle))
				+ m_points[i].GetMultiAxesValue(Z, sin(rotateAngle));
			zVal = -m_points[i].GetMultiAxesValue(X, sin(rotateAngle))
				+ m_points[i].GetMultiAxesValue(Z, cos(rotateAngle));

			m_points[i].SetAxesValue(X, xVal + X_Center);
			m_points[i].SetAxesValue(Z, zVal + Z_Center);

			break;
		case Z:
			m_points[i].SetAxesValue(X, m_points[i].X() - X_Center);
			m_points[i].SetAxesValue(Y, m_points[i].Y() - Y_Center);

			xVal = m_points[i].GetMultiAxesValue(X, cos(rotateAngle))
				- m_points[i].GetMultiAxesValue(Y, sin(rotateAngle));
			yVal = m_points[i].GetMultiAxesValue(X, sin(rotateAngle))
				+ m_points[i].GetMultiAxesValue(Y, cos(rotateAngle));

			m_points[i].SetAxesValue(X, xVal + X_Center);
			m_points[i].SetAxesValue(Y, yVal + Y_Center);

			break;
		}
	}
	CalQModelSize();                                    // ���»�ȡstlģ�͵ĳߴ�
	if (m_zMin != m_zMin_Last)                          // ����ת��ģ��Z��߶ȷ����仯, ��ָ�ԭʼZ��߶�
		AxesMove(Z, m_zMin_Last - m_zMin);
	ReCalNormal();                                      // ���¼���ģ���浥λ������
	m_isModelChanged = true;                            // ��ģ���Ѹ��Ĳ�����Ϊtrue��֪ͨӦ�ó�����Ҫ�ػ�ģ��
}


// stlģ����������
void QSTLSolid::OnScale(float fScaleValue)
{
	unsigned long totalPointCount = m_points.count();        // ��ȡstlģ���е�ĸ���
	if (fScaleValue == 1 || totalPointCount == 0)
	{
		return;
	}

	float X_Center = (m_xMin + m_xMax) / 2;
	float Y_Center = (m_yMin + m_yMax) / 2;
	float Z_Center = (m_zMin + m_zMax) / 2;
	float m_zMin_Last = m_zMin;                         // ��¼ģ��Z�᷽����С����, �Ա����ź�ģ�����ڴ�������

	if (X_Center != 0) AxesMove(X, -X_Center);
	if (Y_Center != 0) AxesMove(Y, -Y_Center);
	if (m_zMin != 0) AxesMove(Z, -m_zMin);

	for (unsigned long i = 0; i < totalPointCount; i++)
	{
		m_points[i].MultiAxesValue(X, fScaleValue);
		m_points[i].MultiAxesValue(Y, fScaleValue);
		m_points[i].MultiAxesValue(Z, fScaleValue);
	}
	CalQModelSize();                                    // ���»�ȡstlģ�͵ĳߴ�

	if (X_Center != 0) AxesMove(X, X_Center);
	if (Y_Center != 0) AxesMove(Y, Y_Center);
	if (m_zMin != m_zMin_Last)                          // �����ź�ģ��Z��߶ȷ����仯, ��ָ�ԭʼZ��߶�
		AxesMove(Z, m_zMin_Last - m_zMin);
	m_isModelChanged = true;                            // ��ģ���Ѹ��Ĳ�����Ϊtrue��֪ͨӦ�ó�����Ҫ�ػ�ģ��
}

// stlģ��x������
void QSTLSolid::OnScale(AxisId axes, float fScaleValue)
{
	m_xMin = 1000;
	m_xMax = -1000;
	unsigned long totalPointCount = m_points.count();        // ��ȡstlģ���е�ĸ���
	if (totalPointCount == 0)
	{
		return;
	}
	for (unsigned long i = 0; i < totalPointCount; i++)
	{
		m_points[i].MultiAxesValue(axes, fScaleValue);
	}
	CalQModelSize();                                    // ���»�ȡstlģ�͵ĳߴ�
	m_isModelChanged = true;                            // ��ģ���Ѹ��Ĳ�����Ϊtrue��֪ͨӦ�ó�����Ҫ�ػ�ģ��
}

// �ж�ģ���Ƿ��ڴ�ӡ������
bool QSTLSolid::IsModelInMachine(int nBuildSize_X, int nBuildSize_Y, int nBuildSize_Z)
{
	// �ж�ģ�ͳߴ��Ƿ�С��0, ��ģ�ͳߴ��Ƿ��쳣
	if (nBuildSize_X <= 0 || nBuildSize_Y <= 0 || nBuildSize_Z <= 0)
	{// ģ�ͳߴ��쳣, ����ģ�ͳߴ粻�ڴ�ӡ������
		return false;
	}

	if (m_xMin <= -nBuildSize_X / 2 || m_xMax >= nBuildSize_X / 2
		|| m_yMin <= -nBuildSize_Y / 2 || m_yMax >= nBuildSize_Y / 2
		|| abs(m_zMin) >  1e-6 || m_zMax >= nBuildSize_Z)
	{//Ϊ��ӡ��ȫ��������ܸպõ��ڴ�ӡ�ߴ磬��Ӧ����С
		return false;
	}
	return true;
}

// ����stl�㡢������
void QSTLSolid::ModelBackUp()
{
	m_points_backup = m_points;
	m_faces_backup = m_faces;
	m_isModelChanged = false;			                // ����ģ�ͳߴ�Ϊδ�����ı�
}

// ��ԭ��֮ǰ�����ģ��
void QSTLSolid::ModelRestore()
{
	m_points = m_points_backup;                     // �������ݵ�����
	m_faces = m_faces_backup;

	m_fRotationValue.SetAxesValue(X, 0);
	m_fRotationValue.SetAxesValue(Y, 0);
	m_fRotationValue.SetAxesValue(Z, 0);
	m_Model_Center.SetAxesValue(X, 0);
	m_Model_Center.SetAxesValue(Y, 0);
	m_Model_Center.SetAxesValue(Z, 0);

	CalQModelSize();                                    // ���»�ȡstlģ�͵ĳߴ�
	m_isModelChanged = false;			                // ����ģ�ͳߴ�Ϊδ�����ı�
}

// �ж�ģ���Ƿ��޸�
bool QSTLSolid::IsModelChanged()
{
	return m_isModelChanged;
}

// ��ȡstlģ�͵ĳߴ�
void QSTLSolid::CalQModelSize()
{
	m_xMin = 10000;
	m_xMax = -10000;
	m_yMin = 10000;
	m_yMax = -10000;
	m_zMin = 10000;
	m_zMax = -10000;

	unsigned long totalPoints = m_points.count();			// ��ȡģ���е�ĸ���
	for (unsigned long i = 0; i < totalPoints; i++)				// ����ģ�͵ĳߴ�
	{
		SetMinMaxVal(m_points[i].X(), &m_xMin, &m_xMax);
		SetMinMaxVal(m_points[i].Y(), &m_yMin, &m_yMax);
		SetMinMaxVal(m_points[i].Z(), &m_zMin, &m_zMax);
	}

	float m_x = (m_xMax + m_xMin) / 2;
	float m_y = (m_yMax + m_yMin) / 2;
	float m_z = m_zMin;

	m_Model_Center = QSTLPoint(m_x, m_y, m_z);
}

// ����ģ��Ϊ�ѱ���(��ģ�����޸ı�־��Ϊfalse)
void QSTLSolid::SetFileSaved()
{
	m_isModelChanged = false;
}

// ���������Сֵ(ͨ�������޸���ֵ)
void QSTLSolid::SetMinMaxVal(float val, float& min, float& max)
{
	if (val <= min)	min = val;
	else if (val >= max) max = val;
}

// ���������Сֵ(ͨ������ָ���޸���ֵ)
void QSTLSolid::SetMinMaxVal(float val, float* min, float* max)
{
	if (val <= *min)	*min = val;
	else if (val >= *max) *max = val;
}
