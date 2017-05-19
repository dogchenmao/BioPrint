#include "QSTLSolid.h"
#pragma region 构造、析构函数


QSTLSolid::QSTLSolid(QObject *parent)
: QThread(parent)
{
	Clear();
}

QSTLSolid::~QSTLSolid()
{
	//EndThread();        // 结束加载stl模型线程
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


// 清空stl模型参数
void QSTLSolid::Clear(void)
{
	m_xMin = 1000;
	m_yMin = 1000;                              // 初始化时将最小值设成1000，将最大值设成-1000
	m_zMin = 1000;                              // 为了在接下来比较中使实际的坐标都能比初始时的最小值大，比最大值小
	m_xMax = -1000;                             // 以更新实际stl模型的各轴的最大坐标和最小坐标
	m_yMax = -1000;
	m_zMax = -1000;

	m_fRunFlag = false;                         // 设置初始线程未运行
	m_isModelChanged = false;                   // 设置初始模型未被修改
	m_StlLoadState = STATE_STL_UNLOAD;          // 设置初始模型未加载
	m_points.clear();                       // 清空stl点参数阵列
	m_faces.clear();                        // 清空stl面参数阵列
}


// 获取模型对应轴坐标的极值(isMin = true为获取模型位置的最小值, isMin = false为获取模型位置的最大值)
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

// 获取模型坐标的极值(isMin = true为获取模型位置的最小值, isMin = false为获取模型位置的最大值)
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


// 获取模型尺寸
QSTLPoint QSTLSolid::GetModelSize(void)
{
	float m_x = m_xMax - m_xMin;
	float m_y = m_yMax - m_yMin;
	float m_z = m_zMax - m_zMin;

	return QSTLPoint(m_x, m_y, m_z);
}


// 获取模型中心点坐标
QSTLPoint QSTLSolid::GetModelCenter(void)
{
	return m_Model_Center;
}


// 获取模型旋转角度
QSTLPoint QSTLSolid::GetModelRotation(void)
{
	return m_fRotationValue;
}


// 重新计算模型每个面的单位法向量
void QSTLSolid::ReCalNormal(void)
{
	QSTLPoint PVertex[3];   // 用于临时存储stl模型每个面的三个点坐标
	int vertex_index;

	if (isStlLoaded())       // 判断模型是否已加载,只有在模型已经被加载的情况下才能计算法向量
	{
		int totalFaces = m_faces.count();    // 获取stl模型中面的个数
		for (int i = 0; i < totalFaces; i++)    // 计算stl模型每个面的法向量
		{
			//取出三个点
			for (int j = 0; j < 3; j++)
			{
				vertex_index = m_faces[i].m_points[j];
				PVertex[j] = m_points[vertex_index];
			}
			// 模型每个面的法向量计算(计算方法为联立方程组求解)
			m_faces[i].m_vector_normal.SetAxesValue(X, (PVertex[0].Y() - PVertex[2].Y())*(PVertex[1].Z() - PVertex[2].Z()) - (PVertex[0].Z() - PVertex[2].Z())*(PVertex[1].Y() - PVertex[2].Y()));
			m_faces[i].m_vector_normal.SetAxesValue(Y, (PVertex[0].Z() - PVertex[2].Z())*(PVertex[1].X() - PVertex[2].X()) - (PVertex[1].Z() - PVertex[2].Z())*(PVertex[0].X() - PVertex[2].X()));
			m_faces[i].m_vector_normal.SetAxesValue(Z, (PVertex[0].X() - PVertex[2].X())*(PVertex[1].Y() - PVertex[2].Y()) - (PVertex[1].X() - PVertex[2].X())*(PVertex[0].Y() - PVertex[2].Y()));

			// 对法向量归一化处理
			float tt = m_faces[i].m_vector_normal.X() * m_faces[i].m_vector_normal.X()
				+ m_faces[i].m_vector_normal.Y() * m_faces[i].m_vector_normal.Y()
				+ m_faces[i].m_vector_normal.Z() * m_faces[i].m_vector_normal.Z();
			tt = pow(tt, 0.5);
			//保存单位法向量
			m_faces[i].m_vector_normal.MultiAxesValue(X, 1.0 / tt);
			m_faces[i].m_vector_normal.MultiAxesValue(Y, 1.0 / tt);
			m_faces[i].m_vector_normal.MultiAxesValue(Z, 1.0 / tt);

		}
	}
}
//[功能]		写入流(已二进制格式保存stl文件)
void QSTLSolid::WriteArchive(QFile& archive)
{
	unsigned short word = 0;
	char STLFileHead[80] = "Regenovo file";
	archive.write((char*)(STLFileHead), 80);                        // 写入前80字节文件头

	int faceNum = m_faces.count();
	archive.write((char*)(&faceNum), sizeof(faceNum));

	for (int i = 0; i < faceNum; i++)
	{
		m_faces[i].m_vector_normal.WriteArchive(archive);               // 写入角面片的法向量

		for (int j = 0; j<3; j++)
		{
			m_points[m_faces[i].m_points[j]].WriteArchive(archive);     // 写入3顶点的坐标
		}

		//属性字
		archive.write((char*)(&word), sizeof(word));		        // 写入三角面片的属性信息
	}
}

// 加载stl文件
void QSTLSolid::LoadSTL()
{
	//if (isStlLoadAble())                                                // 判断stl文件是否存在
	//{// stl文件可加载
	//	if (IsThreadRunning())                                          // 判断加载stl线程是否已运行(即是否正在加载stl文件)
	//	{// 加载线程已运行
	//		QString strInfo = _T("");
	//		//strInfo.LoadString(IDS_THREADRUNNING_LOADING_STL);
	//		if (AfxMessageBox(strInfo, MB_YESNO | MB_ICONSTOP) == IDYES)  // 弹出对话框提示
	//		{
	//			EndThread();
	//		}
	//		else
	//		{
	//			return;
	//		}
	//	}
	Clear();                    // 加载新的stl文件前先清空stl模型参数
	m_fRunFlag = true;				// 因为下面要创建线程并运行，因此先将线程运行标志置为true(这样做存在风险,因为线程可能创建失败)
	run();              // 创建加载stl文件线程
	//}
}
// 判断stl文件是否是ASCII形式
bool QSTLSolid::IsAsciiStlFile(ifstream& ifstream, long& filePtr)
{
	filePtr = 0;
	char buff[101];
	char* p = NULL;
	for (int i = 0; i < 20; i++)                    // 获取前20行数据,若此数据中没有"FACET"字符串,则判断此stl文件不是ASCII类型
	{
		if (ifstream.eof()) break;                  // 遇到文件结束直接跳出

		ifstream.getline(buff, sizeof(buff)-1);   // 获取一行数据(每行最多取100个数据, 最后1字节存放'\0')
		strcat_s(buff, "\0");                       // 往字符串末尾添加'\0'

		if (ifstream.bad())                         // 判断传入的参数是否有问题
		{
			return false;
		}
		_strupr_s(buff);                            // 将字符串全部转换成大写
		p = strstr(buff, "FACET");
		if (p != NULL)                              // 查找第一次出现"FACET"的位置(若找到字符串直接返回true，表示此stl文件为ASCII类型)
		{
			return true;
		}
		filePtr = filePtr + strlen(buff);           // 更新已读取数据的长度, 用于返回"FACET"字符串的位置
	}

	return false;
}
// 获取ASCII形式stl文件关键字
bool QSTLSolid::ReadKeyword(istream& istream, const char* keyword)
{
	char buff[25];
	istream >> buff;
	if (istream.bad())
	{
		//"ReadKeyword打开STL文件出错!"
		return false;
	}
	if (_strnicmp(buff, keyword, sizeof(buff)))				// 判断读取的信息是否为关键字,即是否为keyword
	{
		//"STL文件中有错误, 是否停止执行应用程序?位于："
		return false;
	}

	return true;
}

void QSTLSolid::run()
{
	unsigned long fileSize = 0;                             // stl文件大小
	unsigned long totalFaces = 0;                           // stl模型总面数
	unsigned long pointCounter = 0;                         // stl模型点计数器 
	unsigned long edgeCounter = 0;                          // stl模型边计数器 
	unsigned long faceCounter = 0;                          // stl模型面计数器
	QSTLPoint point;                                // 临时存放stl模型点坐标信息
	QSTLFace face;                                  // 临时存放stl模型面信息

	//***************************************************************/
	//**************************读取stl文件**************************
	//***************************************************************/

	//SetCurrState(pThreadInfo, STATE_STL_LOADING);                       // 设置当前状态为stl文件加载中...
	QString str = m_strPathName_STL;								 // 获取stl文件名
	ifstream inputFile(str.toStdString().c_str(), ios::in | ios::_Nocreate);				 // 以只读方式打开stl文件
	str.clear();
	if (inputFile.bad())                                                // 判断文件是否已损坏
	{// 文件已损坏
		goto LOAD_ERROR;
	}
	inputFile.seekg(0, ios::end);                                       // 定位到文件结尾，用于获取文件长度

	if ((fileSize = inputFile.tellg()) == -1L)                          // 判断是否是空文件
	{// 空文件
		goto LOAD_ERROR;
	}
	inputFile.seekg(0, ios::beg);                                       // 重新返回文件头

	//***************************************************************/
	//**************************判断stl文件格式**********************
	//****************************BINARY/ASCII***********************
	//***************************************************************/
	long filePtr;                                                       // ASCII类型stl文件字符串"facet"的偏移量
	STLFILETYPE fileType = NONSTLFILE;                                  // stl文件类型(初始化为非stl文件)

	if (IsAsciiStlFile(inputFile, filePtr))                             // 判断文件格式为ASCII类型还是BINARY类型
	{// stl文件为ASCII类型
		inputFile.seekg(filePtr, ios::beg);	                            // 定位到字符串"facet"处
		fileType = ASCIISTLFILE;				                        // 标记为ASCII文件
	}
	else
	{// stl文件为BINARY类型
		inputFile.close();                                              // 关闭文件,以便下一步以二进制形式打开文件
		inputFile.open(m_strPathName_STL.toStdString().c_str(), ios::in | ios::_Nocreate | ios::binary);     // 以二进制形式打开stl文件
		inputFile.seekg(80, ios::beg);                                  // 跳过前80字节文件头

		if (fileSize < 134)                                             // 一个完整二进制STL文件至少为134字节(80+4+50)
		{
			goto LOAD_ERROR;
		}

		if (inputFile.bad())                                            // 不可读文件
		{
			goto LOAD_ERROR;
		}

		inputFile.read((char*)(&totalFaces), sizeof (totalFaces));      // 取得stl模型总面数(4 bytes)

		if (inputFile.bad())
		{
			goto LOAD_ERROR;
		}
		if (totalFaces <= 0)                                            // 判断stl模型面片数是否小于或等于零
		{// 小于等于0直接跳出
			goto LOAD_ERROR;
		}
		if (fileSize != 84 + totalFaces * 50)                           // 文件大小不正常(84 + 50的整数倍)
		{
			goto LOAD_ERROR;
		}
		fileType = BINSTLFILE;                                          // 如果都上述条件都符合,则认为此stl文件为二进制类型
	}

	//***************************************************************/
	//                           读取stl文件内容
	//                    inputFile已经定位到数据部分
	//***************************************************************/
	float fIterStep = 0;                            // 1%的stl文件大小,用于进度条显示
	int nOldStep = 0;                               // 此变量用于判断当前的进度和上次执行的进度有无差别，有差别时，更新此变量，并刷新进度条

	if (fileType == ASCIISTLFILE)                   // stl文件为ASCII类型
	{
		fIterStep = fileSize / 100.0;                                   // 将文件总长度分成100份，用于显示加载进度
		char buff[25];                                                  // 用于临时存放从文件中读取的数据
		unsigned long  nPosition = 0;                                            // 当前读取到文件数据的位置
		while (m_fRunFlag && nPosition < fileSize)
		{
			nPosition = inputFile.tellg();                              // 获取当前已读取文件长度
			int nTem = nPosition / fIterStep;                           // fIterStep为总长度的1%，nPosition为已读取的长度，计算的结果nTem为读取文件的百分比
			if (nOldStep != nTem)                                       // 判断当前加载的进度和上次有无差别
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);                          // 刷新进度条
			}

			inputFile >> buff;

			// 下面为对ASCII类型的stl文件的解析, 需要对stl文件格式有一定了解
			// 如果获取当前数据不是"facet"则退出(因为进入此循环前已经将文件指针定位到此字符串前面了)
			if (_strnicmp(buff, "facet", 5) != 0)
				break;
			// Read normal vector 读取法向量
			if (!ReadKeyword(inputFile, "normal"))                      // 判断当前字符串是不是"normal"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			point.ReadSTLFile(inputFile, fileType);                     // 获取平面法向量
			face.m_vector_normal = point;

			// Read three Points
			if (!ReadKeyword(inputFile, "outer"))                       // 判断当前字符串是不是"outer"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			if (!ReadKeyword(inputFile, "loop"))                        // 判断当前字符串是不是"loop"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			for (int i = 0; i<3; i++)                                   // 获取三角面片三个顶点坐标
			{
				if (!ReadKeyword(inputFile, "vertex"))
				{
					inputFile.close();
					goto LOAD_ERROR;
				}

				point.ReadSTLFile(inputFile, fileType);                 // 读取点坐标
				m_points.append(point);                       // 将坐标添加到stl文件点参数阵列中
				face.m_points[i] = pointCounter;                        // 更新stl模型平面的3个顶点的索引
				SetMinMaxVal(point.X(), m_xMin, m_xMax);
				SetMinMaxVal(point.Y(), m_yMin, m_yMax);        // 更新模型尺寸
				SetMinMaxVal(point.Z(), m_zMin, m_zMax);
				pointCounter++;
			}

			if (!ReadKeyword(inputFile, "endloop"))                     // 判断当前字符串是不是"endloop"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}

			if (!ReadKeyword(inputFile, "endfacet"))                    // 判断当前字符串是不是"endfacet"
			{
				inputFile.close();
				goto LOAD_ERROR;
			}
			// 注: pThreadInfo->m_faces.Add(face); faceCounter++; <==> pThreadInfo->m_faces.SetAt(faceCounter++, face);
			m_faces.append(face);
			faceCounter++;

			//pThreadInfo->DoEvent();
		}
		if (!m_fRunFlag)                                   // 判断线程是否还在运行
		{
			goto LOAD_ERROR;
		}
		totalFaces = faceCounter;

		// 判断ASCII形式的stl文件是否已"endfacet"字符串结束
		if (_strnicmp(buff, "endsolid", sizeof(buff)) != 0)
		{
			inputFile.close();
			goto LOAD_ERROR;
		}

	}
	else if (fileType == BINSTLFILE)                // stl文件为ASCII类型
	{
		// 读取二进制stl文件
		try
		{
			m_faces.resize(totalFaces);                   // 设置stl面阵列大小
			m_points.resize(totalFaces * 3);              // 设置stl点阵列大小
		}
		catch (QException*)
		{
			QMessageBox::information(NULL, "ERROR", "Memory allocation failure!");
			goto LOAD_ERROR;
		}


		////////////////////////////////////////////////////////////
		fIterStep = totalFaces / 100.0;                                 // 将文件总长度分成100份，用于显示加载进度

		for (unsigned long counter = 0; counter < totalFaces && m_fRunFlag; counter++)
		{
			if (inputFile.eof())                                        // 容错处理, 判断文件是否已读完
			{
				if (counter + 1 != totalFaces)                          // 文件已经读完了,但是三角面片个数不等于totalFaces
				{
					QMessageBox::information(NULL, "ERROR", "Practical reading patch does not match!");
				}
				totalFaces = counter;
				m_faces.resize(totalFaces);               // 设置stl面阵列大小
				m_points.resize(totalFaces * 3);          // 设置stl点阵列大小
				break;
			}

			int nTem = faceCounter / fIterStep;                         // fIterStep为总长度的1%，faceCounter为已读取的长度，计算的结果nTem为读取文件的百分比
			if (nOldStep != nTem)                                       // 判断当前加载的进度和上次有无差别
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);                          // 更新进度条
			}

			// 读取法向量
			point.ReadSTLFile(inputFile, fileType);
			face.m_vector_normal = point;

			// 读取三个点
			for (int i = 0; i < 3 && m_fRunFlag; i++)
			{
				point.ReadSTLFile(inputFile, fileType);
				m_points.replace(pointCounter, point);
				face.m_points[i] = pointCounter;
				SetMinMaxVal(point.X(), m_xMin, m_xMax);
				SetMinMaxVal(point.Y(), m_yMin, m_yMax);        // 更新模型尺寸
				SetMinMaxVal(point.Z(), m_zMin, m_zMax);
				pointCounter++;
			}

			m_faces.replace(faceCounter++, face);

			// 读取文件属性
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
	if (!m_fRunFlag)                                       // 线程未运行
	{
		goto LOAD_ERROR;
	}
	inputFile.close();                                                  // 关闭文件
	MovetoCenter();                                        // 将模型移动到中心
	ModelBackUp();                                         // 备份模型数据
	//SetCurrState(pThreadInfo, STATE_STL_LOADED);                        // 设置stl文件加载状态为"已加载"
	m_fRunFlag = false;                                    // 将stl文件运行标志置为false, 代表stl文件已加载完成

LOAD_ERROR:
	inputFile.close();                                                  // 关闭文件
	//SetCurrState(pThreadInfo, STATE_STL_LOADFAILED);                    // 设置stl文件加载状态为"加载失败"
	m_fRunFlag = false;                                    // 将stl文件运行标志置为false, 代表stl文件已加载完成
	//m_hThreadHandle = NULL;                                // 清空stl文件加载线程句柄
}

// 模型平移
void QSTLSolid::AxesMove(AxisId axes, float movedlength)
{
	unsigned long totalPointCount = m_points.count();        // 获取stl模型中点的个数

	if (totalPointCount == 0)
	{
		return;
	}

	for (unsigned long i = 0; i < totalPointCount; i++)			// 更新平移后模型的数据
	{
		m_points[i].AddAxesValue(axes, movedlength);
	}
	CalQModelSize();                                    // 重新获取stl模型的尺寸
	m_isModelChanged = true;                            // 将模型已更改参数置为true，通知应用程序需要重绘模型
}
// 模型移动到平台
void QSTLSolid::MovetoPlateform()
{
	if (abs(m_zMin) > 0)                                 // 判断模型是否已经在平台上
	{
		AxesMove(Z, -m_zMin);
	}
}
// 模型移动到中心(Z轴保持不变)
void QSTLSolid::MovetoCenter()
{
	double movevalue = .0f;
	movevalue = (m_xMax + m_xMin) / 2;                  // 获取模型当前位置中心点X坐标
	if (abs(movevalue) > 1e-6)                          // 判断模型是否已经在中心
	{
		AxesMove(X, -movevalue);
	}

	movevalue = (m_yMax + m_yMin) / 2;                  // 获取模型当前位置中心点Y坐标
	if (abs(movevalue) > 1e-6)                          // 判断模型是否已经在中心
	{
		AxesMove(Y, -movevalue);
	}
}

// 沿坐标轴逆时针旋转模型
void QSTLSolid::OnRotation(AxisId axes, float fRotationValue)
{
	double xVal, yVal, zVal;
	double rotateAngle = fRotationValue * 3.1415926535898 / 180.0;              // 将转换角度转化为弧度

	unsigned long totalPoints = m_points.count();            // 获取stl模型中点的个数

	m_fRotationValue.SetAxesValue(axes, (int)(m_fRotationValue.GetAxesValue(axes) + fRotationValue + 360) % 360);    // 更新对应轴的旋转角度

	if (totalPoints == 0)
	{
		return;
	}

	float X_Center = (m_xMin + m_xMax) / 2;
	float Y_Center = (m_yMin + m_yMax) / 2;
	float Z_Center = (m_zMin + m_zMax) / 2;
	float m_zMin_Last = m_zMin;                         // 记录模型Z轴方向最小坐标, 以便旋转后模型仍在此坐标上

	for (unsigned long i = 0; i < totalPoints; i++)             // 对stl模型每个点均进行旋转(逆时针旋转公式为:x'=x*cosθ-y*sinθ   y'=x*sinθ+cosθ)
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
	CalQModelSize();                                    // 重新获取stl模型的尺寸
	if (m_zMin != m_zMin_Last)                          // 若旋转后模型Z轴高度发生变化, 则恢复原始Z轴高度
		AxesMove(Z, m_zMin_Last - m_zMin);
	ReCalNormal();                                      // 重新计算模型面单位法向量
	m_isModelChanged = true;                            // 将模型已更改参数置为true，通知应用程序需要重绘模型
}


// stl模型整体缩放
void QSTLSolid::OnScale(float fScaleValue)
{
	unsigned long totalPointCount = m_points.count();        // 获取stl模型中点的个数
	if (fScaleValue == 1 || totalPointCount == 0)
	{
		return;
	}

	float X_Center = (m_xMin + m_xMax) / 2;
	float Y_Center = (m_yMin + m_yMax) / 2;
	float Z_Center = (m_zMin + m_zMax) / 2;
	float m_zMin_Last = m_zMin;                         // 记录模型Z轴方向最小坐标, 以便缩放后模型仍在此坐标上

	if (X_Center != 0) AxesMove(X, -X_Center);
	if (Y_Center != 0) AxesMove(Y, -Y_Center);
	if (m_zMin != 0) AxesMove(Z, -m_zMin);

	for (unsigned long i = 0; i < totalPointCount; i++)
	{
		m_points[i].MultiAxesValue(X, fScaleValue);
		m_points[i].MultiAxesValue(Y, fScaleValue);
		m_points[i].MultiAxesValue(Z, fScaleValue);
	}
	CalQModelSize();                                    // 重新获取stl模型的尺寸

	if (X_Center != 0) AxesMove(X, X_Center);
	if (Y_Center != 0) AxesMove(Y, Y_Center);
	if (m_zMin != m_zMin_Last)                          // 若缩放后模型Z轴高度发生变化, 则恢复原始Z轴高度
		AxesMove(Z, m_zMin_Last - m_zMin);
	m_isModelChanged = true;                            // 将模型已更改参数置为true，通知应用程序需要重绘模型
}

// stl模型x轴缩放
void QSTLSolid::OnScale(AxisId axes, float fScaleValue)
{
	m_xMin = 1000;
	m_xMax = -1000;
	unsigned long totalPointCount = m_points.count();        // 获取stl模型中点的个数
	if (totalPointCount == 0)
	{
		return;
	}
	for (unsigned long i = 0; i < totalPointCount; i++)
	{
		m_points[i].MultiAxesValue(axes, fScaleValue);
	}
	CalQModelSize();                                    // 重新获取stl模型的尺寸
	m_isModelChanged = true;                            // 将模型已更改参数置为true，通知应用程序需要重绘模型
}

// 判断模型是否在打印区域内
bool QSTLSolid::IsModelInMachine(int nBuildSize_X, int nBuildSize_Y, int nBuildSize_Z)
{
	// 判断模型尺寸是否小于0, 即模型尺寸是否异常
	if (nBuildSize_X <= 0 || nBuildSize_Y <= 0 || nBuildSize_Z <= 0)
	{// 模型尺寸异常, 返回模型尺寸不在打印区域内
		return false;
	}

	if (m_xMin <= -nBuildSize_X / 2 || m_xMax >= nBuildSize_X / 2
		|| m_yMin <= -nBuildSize_Y / 2 || m_yMax >= nBuildSize_Y / 2
		|| abs(m_zMin) >  1e-6 || m_zMax >= nBuildSize_Z)
	{//为打印安全起见，不能刚好等于打印尺寸，而应该略小
		return false;
	}
	return true;
}

// 备份stl点、面数据
void QSTLSolid::ModelBackUp()
{
	m_points_backup = m_points;
	m_faces_backup = m_faces;
	m_isModelChanged = false;			                // 设置模型尺寸为未发生改变
}

// 还原到之前保存的模型
void QSTLSolid::ModelRestore()
{
	m_points = m_points_backup;                     // 导出备份的数据
	m_faces = m_faces_backup;

	m_fRotationValue.SetAxesValue(X, 0);
	m_fRotationValue.SetAxesValue(Y, 0);
	m_fRotationValue.SetAxesValue(Z, 0);
	m_Model_Center.SetAxesValue(X, 0);
	m_Model_Center.SetAxesValue(Y, 0);
	m_Model_Center.SetAxesValue(Z, 0);

	CalQModelSize();                                    // 重新获取stl模型的尺寸
	m_isModelChanged = false;			                // 设置模型尺寸为未发生改变
}

// 判断模型是否被修改
bool QSTLSolid::IsModelChanged()
{
	return m_isModelChanged;
}

// 获取stl模型的尺寸
void QSTLSolid::CalQModelSize()
{
	m_xMin = 10000;
	m_xMax = -10000;
	m_yMin = 10000;
	m_yMax = -10000;
	m_zMin = 10000;
	m_zMax = -10000;

	unsigned long totalPoints = m_points.count();			// 获取模型中点的个数
	for (unsigned long i = 0; i < totalPoints; i++)				// 计算模型的尺寸
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

// 设置模型为已保存(将模型已修改标志置为false)
void QSTLSolid::SetFileSaved()
{
	m_isModelChanged = false;
}

// 设置最大、最小值(通过引用修改最值)
void QSTLSolid::SetMinMaxVal(float val, float& min, float& max)
{
	if (val <= min)	min = val;
	else if (val >= max) max = val;
}

// 设置最大、最小值(通过传递指针修改最值)
void QSTLSolid::SetMinMaxVal(float val, float* min, float* max)
{
	if (val <= *min)	*min = val;
	else if (val >= *max) *max = val;
}
