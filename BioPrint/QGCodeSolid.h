#pragma once

#include <QObject>
#include <QVector>
#include <QThread>
#include <QException>
#include <QMessageBox>

#include <io.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "GlobleDefine.h"
#include "Q2DLines.h"
#include "QGCodeParser.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////
////	GCode文件操作的特性、方法
//////////////////////////////////////////////////////////////////////////

//GCode文件导入状态：（未加载、加载中、已加载）
enum GCode_LOAD_STATE
{
	STATE_GCODE_UNLOAD = GCODE_UNLOAD,              // GCode文件未加载
	STATE_GCODE_LOADING = GCODE_LOADING,            // GCode文件加载中
	STATE_GCODE_LOADED = GCODE_LOADED,              // GCode文件已加载
};

class QGCodeSolid : public QThread
{
	Q_OBJECT

public:
	QGCodeSolid(QObject *parent = nullptr)
	{
		Init();             // 初始化变量
	}
	~QGCodeSolid(void)
	{
		Clear();            // 终止线程并清空变量
	}
private:
	HWND m_hNotifyWnd;
	//GCode加载状态
	GCode_LOAD_STATE m_GCodeLoadState;
	//GCode生成器
	//QGCodeGenerator m_GCodeGenerator;
	//stl文件名称
	QString m_strPathName_STL;
	//GCode文件名称
	QString m_strPathName_GCode;
	//线程运行标志
	volatile bool m_fRunFlag;
	//GCode文件存储结构
	QVector<QString> m_strGCodes;
	//GCode备份
	QVector<QString> m_strGCodesBackup;
	//路径存储结构
	QVector<Q2DLines> m_ModelPaths;
	// 打印所需时间
	double m_TimesNeed;
	//是否可执行GCode加载线程
	bool isGCodeLoadAble(bool isAutoGenerate);
public:
	//初始化
	inline void Init()
	{
		m_hNotifyWnd = NULL;
		// 初始化设置GCode加载状态为未加载状态
		m_GCodeLoadState = STATE_GCODE_UNLOAD;
		////GCode生成器
		//m_GCodeGenerator;
		//stl文件名称
		m_strPathName_STL = "";
		//GCode文件名称
		m_strPathName_GCode = "";
		//线程运行循环标志
		m_fRunFlag = false;
		//GCode加载线程句柄
		//m_hThreadHandle = NULL;	//辅助线程
		////GCode文件存储结构
		//m_strGCodes;
	}
	//程序退出
	inline void Destroy()
	{
		Clear();
	}
	//准备好 重新加载
	inline void Clear()
	{
		//EndThread(500);
		m_strPathName_GCode = "";
		m_strGCodes.clear();
		m_strGCodesBackup.clear();
		m_ModelPaths.clear();
		//m_GCodeGenerator.Clear();
		m_GCodeLoadState = STATE_GCODE_UNLOAD;
	}
	inline void Reload()
	{
		//EndThread(500);
		//准备好重新加载
		m_strGCodes.clear();
		m_strGCodesBackup.clear();
		m_ModelPaths.clear();
		//m_GCodeGenerator.Reload();
		m_GCodeLoadState = STATE_GCODE_UNLOAD;
	}

	//是否已成功加载GCode
	inline bool isGCodeLoaded()
	{
		return m_GCodeLoadState == STATE_GCODE_LOADED;
	}


	inline QVector<QString> & GetGCodeLines()
	{
		return m_strGCodes;
	}

	inline QVector<QString> & GetGCodeBackupLines()
	{
		m_strGCodes.clear();
		m_strGCodes.append(m_strGCodesBackup);
		return m_strGCodes;
	}

	inline QVector<Q2DLines>& GetPathLines()
	{
		return m_ModelPaths;
	}

	//inline CGCodeGenerator& GetGCodeGenerator()
	//{
	//	return m_GCodeGenerator;
	//}
	inline double GetTimeNeed()
	{
		return m_TimesNeed;
	}
	inline void SetWnd(HWND hWnd)
	{
		m_hNotifyWnd = hWnd;
		//m_GCodeGenerator.SetWnd(m_hNotifyWnd);
	}

	inline void SetPathName_GCode(QString str)
	{
		m_strPathName_GCode = str;
		//m_GCodeGenerator.SetPathName_GCode(str);
	}

	inline void SetPathName_STL(QString str)
	{
		m_strPathName_STL = str;
		//m_GCodeGenerator.SetPathName_STL(str);
	}

	void LoadGCode(bool isAutoGenerate);
	//// 设置GCode文件加载状态并通知响应事件
	//static void SetCurrState(CGCodeSolid* pThreadInfo, GCode_LOAD_STATE state)
	//{
	//	m_GCodeLoadState = state;
	//	::PostMessage(m_hNotifyWnd, ON_PROCESS_CHANGE, PROGRESS_STYLE, (LPARAM)state);
	//}

	//static void SetCurrPos(CGCodeSolid* pThreadInfo, int nPos)
	//{
	//	::PostMessage(m_hNotifyWnd, ON_PROCESS_CHANGE, PROGRESS_VALUE, nPos);
	//}

private:

		// 获取并检验读取的文件是否含有'('  ';'  '；'  '\0'
		static QString GCodePick(char* szline, int nLen)
		{
			QString str = "";
			if (nLen > 0)
			{
				int nCount = 0;
				char cCur = szline[nCount];
				while (cCur != '(' && cCur != ';' && cCur != '；' && cCur != '\0')
				{
					cCur = szline[++nCount];
				}
				str = QString(szline);
			}
			return str;
		}
private:
	void run()
	{

		wchar_t szfilePath[256] = { 0 };
		m_strPathName_GCode.toWCharArray(szfilePath);
		m_strPathName_GCode.clear();
		//SetCurrState(pThreadInfo, STATE_GCODE_LOADING);
		m_strGCodes.clear();                                   // 移除原先文件中GCode数据
		m_strGCodesBackup.clear();

		char szLine[256] = { 0 };
		unsigned long nIndex = 0;								// 已加载文件的长度
		unsigned long nStrLineLength = 0;						// 每一行GCode指令的长度
		unsigned long nFileLength = 0;							// 文件长度变量
		unsigned long nOldStep = 0;								// 上一个循环中GCode文件加载的进度
		float nIterStep = 0;							// 1%文件长度对应的大小
		//用于计算耗时、
		QGCodeParser GCodeParser;
		QString strLastCodeLine = "";
		//
		ifstream f_GCodeFile(szfilePath, ios::in | ios::_Nocreate);             // 打开GCode文件
		if (f_GCodeFile.bad())
		{
			f_GCodeFile.close();
			goto ERROR_ZOON;
		}
		f_GCodeFile.seekg(0, ios::end);               // 指针移动到文件末尾
		nIndex = 0;
		nStrLineLength = 0;
		nFileLength = f_GCodeFile.tellg();              // 获取文件长度
		f_GCodeFile.seekg(0, ios::beg);                  // 指针重新移动到文件头

		if (nFileLength <= 0)
		{
			goto ERROR_ZOON;
		}

		nIterStep = nFileLength / 100.0;               // 将文件总长度分成100份，用于显示加载进度
		nOldStep = -1;

		while (m_fRunFlag && nIndex < nFileLength)
		{
			int nTem = nIndex / nIterStep;              // nIterStep为总长度的1%，nIndex为已加载的长度，计算的结果nTem为加载文件的百分比
			if (nOldStep != nTem)
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);          // 刷新进度条
			}

			if (f_GCodeFile.eof())						// 文件加载完成
				break;
			memset(szLine, 0, 256);                       // 清空缓存
			try
			{
				f_GCodeFile.getline(szLine, 254);       // 读取1行数据, 最多读取254个字符

				if (f_GCodeFile.bad())
				{
					goto ERROR_ZOON;
				}

				nStrLineLength = strlen(szLine);        // 统计获取数据的长度
				if (nStrLineLength <= 0)
				{
					continue;
				}
				nIndex += nStrLineLength;               // 更新已加载文件的长度

				QString strGCodeSource = GCodePick(szLine, nStrLineLength);     // 获取并检验读取的文件是否含有'('  ';'  '；'  '\0'
				QString strGCodeLine = strGCodeSource;

				if (GCodeParser.IsG1(strGCodeSource))   // 判断是否是G1指令
				{
					G1Pick G1Values, G1Values_temp;
					//取出G1值存入G1Values_temp中
					GCodeParser.PickG1Value(G1Values_temp, strGCodeSource);
					//反转坐标，将翻转后的GCode指令存入strGCodeLine
					GCodeParser.G1_CheckReviser(G1Values_temp, strGCodeLine);
					//取出反转坐标后的G1值,存入G1Values(因为无法存入G1Values_temp, 所以使用一个新变量)
					GCodeParser.PickG1Value(G1Values, strGCodeLine);
					//时间计算，同时更新GCodeParser变量
					m_TimesNeed += GCodeParser.CalcG1Times(G1Values);
					//路径数据保存
					if (GCodeParser.IsExtruderON())
					{
						int nPathArrayCount = m_ModelPaths.count();
						if (nPathArrayCount > 0)
						{
							Q2DLines& PathArray = m_ModelPaths[nPathArrayCount - 1];
							//PathArray.append(GCodeParser.GetCurrentPos_Offset(Point5D(theApp.m_SystemConfig.m_nGCodeOffset_X + theApp.m_SystemConfig.m_PlatformCenter_Pos.X, theApp.m_SystemConfig.m_nGCodeOffset_Y + theApp.m_SystemConfig.m_PlatformCenter_Pos.Y, 0)));
						}
					}
					strLastCodeLine = strGCodeSource;
				}
				else if (GCodeParser.IsM101(strGCodeSource))
				{//打开挤出机
					Q2DLines PathArray;
					G1Pick G1Values, G1Values_temp;
					//取出G1值存入G1Values_temp中
					GCodeParser.PickG1Value(G1Values_temp, strLastCodeLine);
					//反转坐标，将翻转后的GCode指令存入strGCodeLine
					GCodeParser.G1_CheckReviser(G1Values_temp, strGCodeLine);
					//取出反转坐标后的G1值,存入G1Values(因为无法存入G1Values_temp, 所以使用一个新变量)
					GCodeParser.PickG1Value(G1Values, strGCodeLine);
					GCodeParser.CalcG1Times(G1Values);          // 并非用于计算时间，而是用于更新GCodeParser变量
					//PathArray.push_back(GCodeParser.GetCurrentPos_Offset(Point5D(theApp.m_SystemConfig.m_nGCodeOffset_X + theApp.m_SystemConfig.m_PlatformCenter_Pos.X, theApp.m_SystemConfig.m_nGCodeOffset_Y + theApp.m_SystemConfig.m_PlatformCenter_Pos.Y, 0)));
					
					m_ModelPaths.append(PathArray);

					strGCodeLine = strGCodeSource;
				}
				else if (GCodeParser.IsM103(strGCodeSource))
				{//关闭挤出机
				}

				if (strGCodeLine.length() > 0)
				{
					m_strGCodes.append(strGCodeLine);
				}
			}
			catch (QException*)
			{
				QMessageBox::information(NULL, "ERROR", "Memory allocation failure!");
				goto ERROR_ZOON;
			}
			//catch (CMemoryException*)
			//{
			//	AfxMessageBox(_T("Insufficient memory!"));
			//	goto ERROR_ZOON;
			//}
			//catch (CFileException*)
			//{
			//	AfxMessageBox(_T("File read exception!"));
			//	goto ERROR_ZOON;
			//}
			//catch (CException*)
			//{
			//	AfxMessageBox(_T("unknown exception!"));
			//	goto ERROR_ZOON;
			//}
		}
		if (!m_fRunFlag)
		{
			goto ERROR_ZOON;
		}

		int nPackageCount = m_strGCodes.count();
		if (nPackageCount > 0)
		{
			m_strGCodesBackup.clear();
			m_strGCodesBackup.append(m_strGCodes);
			m_fRunFlag = false;
			//SetCurrState(pThreadInfo, STATE_GCODE_LOADED);
			f_GCodeFile.close();
			return;
		}
	ERROR_ZOON:
		m_fRunFlag = false;
		//m_hThreadHandle = NULL;
		//SetCurrState(pThreadInfo, STATE_GCODE_UNLOAD);
		f_GCodeFile.close();
		return;
	}
};
