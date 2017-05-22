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
////	GCode�ļ����������ԡ�����
//////////////////////////////////////////////////////////////////////////

//GCode�ļ�����״̬����δ���ء������С��Ѽ��أ�
enum GCode_LOAD_STATE
{
	STATE_GCODE_UNLOAD = GCODE_UNLOAD,              // GCode�ļ�δ����
	STATE_GCODE_LOADING = GCODE_LOADING,            // GCode�ļ�������
	STATE_GCODE_LOADED = GCODE_LOADED,              // GCode�ļ��Ѽ���
};

class QGCodeSolid : public QThread
{
	Q_OBJECT

public:
	QGCodeSolid(QObject *parent = nullptr)
	{
		Init();             // ��ʼ������
	}
	~QGCodeSolid(void)
	{
		Clear();            // ��ֹ�̲߳���ձ���
	}
private:
	HWND m_hNotifyWnd;
	//GCode����״̬
	GCode_LOAD_STATE m_GCodeLoadState;
	//GCode������
	//QGCodeGenerator m_GCodeGenerator;
	//stl�ļ�����
	QString m_strPathName_STL;
	//GCode�ļ�����
	QString m_strPathName_GCode;
	//�߳����б�־
	volatile bool m_fRunFlag;
	//GCode�ļ��洢�ṹ
	QVector<QString> m_strGCodes;
	//GCode����
	QVector<QString> m_strGCodesBackup;
	//·���洢�ṹ
	QVector<Q2DLines> m_ModelPaths;
	// ��ӡ����ʱ��
	double m_TimesNeed;
	//�Ƿ��ִ��GCode�����߳�
	bool isGCodeLoadAble(bool isAutoGenerate);
public:
	//��ʼ��
	inline void Init()
	{
		m_hNotifyWnd = NULL;
		// ��ʼ������GCode����״̬Ϊδ����״̬
		m_GCodeLoadState = STATE_GCODE_UNLOAD;
		////GCode������
		//m_GCodeGenerator;
		//stl�ļ�����
		m_strPathName_STL = "";
		//GCode�ļ�����
		m_strPathName_GCode = "";
		//�߳�����ѭ����־
		m_fRunFlag = false;
		//GCode�����߳̾��
		//m_hThreadHandle = NULL;	//�����߳�
		////GCode�ļ��洢�ṹ
		//m_strGCodes;
	}
	//�����˳�
	inline void Destroy()
	{
		Clear();
	}
	//׼���� ���¼���
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
		//׼�������¼���
		m_strGCodes.clear();
		m_strGCodesBackup.clear();
		m_ModelPaths.clear();
		//m_GCodeGenerator.Reload();
		m_GCodeLoadState = STATE_GCODE_UNLOAD;
	}

	//�Ƿ��ѳɹ�����GCode
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
	//// ����GCode�ļ�����״̬��֪ͨ��Ӧ�¼�
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

		// ��ȡ�������ȡ���ļ��Ƿ���'('  ';'  '��'  '\0'
		static QString GCodePick(char* szline, int nLen)
		{
			QString str = "";
			if (nLen > 0)
			{
				int nCount = 0;
				char cCur = szline[nCount];
				while (cCur != '(' && cCur != ';' && cCur != '��' && cCur != '\0')
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
		m_strGCodes.clear();                                   // �Ƴ�ԭ���ļ���GCode����
		m_strGCodesBackup.clear();

		char szLine[256] = { 0 };
		unsigned long nIndex = 0;								// �Ѽ����ļ��ĳ���
		unsigned long nStrLineLength = 0;						// ÿһ��GCodeָ��ĳ���
		unsigned long nFileLength = 0;							// �ļ����ȱ���
		unsigned long nOldStep = 0;								// ��һ��ѭ����GCode�ļ����صĽ���
		float nIterStep = 0;							// 1%�ļ����ȶ�Ӧ�Ĵ�С
		//���ڼ����ʱ��
		QGCodeParser GCodeParser;
		QString strLastCodeLine = "";
		//
		ifstream f_GCodeFile(szfilePath, ios::in | ios::_Nocreate);             // ��GCode�ļ�
		if (f_GCodeFile.bad())
		{
			f_GCodeFile.close();
			goto ERROR_ZOON;
		}
		f_GCodeFile.seekg(0, ios::end);               // ָ���ƶ����ļ�ĩβ
		nIndex = 0;
		nStrLineLength = 0;
		nFileLength = f_GCodeFile.tellg();              // ��ȡ�ļ�����
		f_GCodeFile.seekg(0, ios::beg);                  // ָ�������ƶ����ļ�ͷ

		if (nFileLength <= 0)
		{
			goto ERROR_ZOON;
		}

		nIterStep = nFileLength / 100.0;               // ���ļ��ܳ��ȷֳ�100�ݣ�������ʾ���ؽ���
		nOldStep = -1;

		while (m_fRunFlag && nIndex < nFileLength)
		{
			int nTem = nIndex / nIterStep;              // nIterStepΪ�ܳ��ȵ�1%��nIndexΪ�Ѽ��صĳ��ȣ�����Ľ��nTemΪ�����ļ��İٷֱ�
			if (nOldStep != nTem)
			{
				nOldStep = nTem;
				//SetCurrPos(pThreadInfo, nTem);          // ˢ�½�����
			}

			if (f_GCodeFile.eof())						// �ļ��������
				break;
			memset(szLine, 0, 256);                       // ��ջ���
			try
			{
				f_GCodeFile.getline(szLine, 254);       // ��ȡ1������, ����ȡ254���ַ�

				if (f_GCodeFile.bad())
				{
					goto ERROR_ZOON;
				}

				nStrLineLength = strlen(szLine);        // ͳ�ƻ�ȡ���ݵĳ���
				if (nStrLineLength <= 0)
				{
					continue;
				}
				nIndex += nStrLineLength;               // �����Ѽ����ļ��ĳ���

				QString strGCodeSource = GCodePick(szLine, nStrLineLength);     // ��ȡ�������ȡ���ļ��Ƿ���'('  ';'  '��'  '\0'
				QString strGCodeLine = strGCodeSource;

				if (GCodeParser.IsG1(strGCodeSource))   // �ж��Ƿ���G1ָ��
				{
					G1Pick G1Values, G1Values_temp;
					//ȡ��G1ֵ����G1Values_temp��
					GCodeParser.PickG1Value(G1Values_temp, strGCodeSource);
					//��ת���꣬����ת���GCodeָ�����strGCodeLine
					GCodeParser.G1_CheckReviser(G1Values_temp, strGCodeLine);
					//ȡ����ת������G1ֵ,����G1Values(��Ϊ�޷�����G1Values_temp, ����ʹ��һ���±���)
					GCodeParser.PickG1Value(G1Values, strGCodeLine);
					//ʱ����㣬ͬʱ����GCodeParser����
					m_TimesNeed += GCodeParser.CalcG1Times(G1Values);
					//·�����ݱ���
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
				{//�򿪼�����
					Q2DLines PathArray;
					G1Pick G1Values, G1Values_temp;
					//ȡ��G1ֵ����G1Values_temp��
					GCodeParser.PickG1Value(G1Values_temp, strLastCodeLine);
					//��ת���꣬����ת���GCodeָ�����strGCodeLine
					GCodeParser.G1_CheckReviser(G1Values_temp, strGCodeLine);
					//ȡ����ת������G1ֵ,����G1Values(��Ϊ�޷�����G1Values_temp, ����ʹ��һ���±���)
					GCodeParser.PickG1Value(G1Values, strGCodeLine);
					GCodeParser.CalcG1Times(G1Values);          // �������ڼ���ʱ�䣬�������ڸ���GCodeParser����
					//PathArray.push_back(GCodeParser.GetCurrentPos_Offset(Point5D(theApp.m_SystemConfig.m_nGCodeOffset_X + theApp.m_SystemConfig.m_PlatformCenter_Pos.X, theApp.m_SystemConfig.m_nGCodeOffset_Y + theApp.m_SystemConfig.m_PlatformCenter_Pos.Y, 0)));
					
					m_ModelPaths.append(PathArray);

					strGCodeLine = strGCodeSource;
				}
				else if (GCodeParser.IsM103(strGCodeSource))
				{//�رռ�����
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
