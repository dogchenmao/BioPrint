#pragma once
#include "QSTLPoint.h"
#include "QSTLFace.h"
#include "GlobleDefine.h"
#include <QThread>
#include <QObject>
#include <fstream>
#include <QException>
#include <QMessageBox>

using namespace std;

typedef QVector<QSTLPoint> STLPointArray;        // QSTLPoint���͵�����
typedef QVector<QSTLFace> STLFaceArray;           // CSTLFace���͵�����

// stl�ļ�����״̬
enum STL_LOAD_STATE
{
	STATE_STL_LOADING = STL_LOADING,           // ������
	STATE_STL_RECONSTRUCT = STL_RECONSTRUCT,           // �ؽ���
	STATE_STL_LOADED = STL_LOADED,		    // �Ѽ���
	STATE_STL_UNLOAD = STL_UNLOAD,		    // δ����
	STATE_STL_LOADFAILED = STL_LOADFAILED,           // ����ʧ��
};

// stlģ����
class QSTLSolid : public QThread
{
	Q_OBJECT
public:
	QSTLSolid(QObject *parent = Q_NULLPTR);
	~QSTLSolid(void);
	const QSTLSolid& operator=(const QSTLSolid&);
private:
	void run();
	//�ڲ�����
private:
	HWND m_hNotifyWnd;                          // stlģ������
	STL_LOAD_STATE m_StlLoadState;              // stl�ļ�����״̬
	QString m_strPathName_STL;                  // stl�ļ���(����·��)
	QString m_strPathName_GCode;                // GCode�ļ���(����·��)
	volatile bool m_fRunFlag;		            // �߳����б�־

	STLPointArray m_points;						// stl�ļ��е��������
	STLFaceArray m_faces;						// stl�ļ������������(1������3�������)
	STLPointArray m_points_backup;			    // stl�ļ��е����ݱ���
	STLFaceArray m_faces_backup;			    // stl�ļ��������ݱ���(1������3�������)
	float m_xMin;                               // stlģ��x����С����
	float m_xMax;                               // stlģ��x���������
	float m_yMin;                               // stlģ��y����С����
	float m_yMax;                               // stlģ��y���������
	float m_zMin;                               // stlģ��z����С����
	float m_zMax;                               // stlģ��z���������
	bool m_isModelChanged;                      // ģ���Ƿ��޸�

	QSTLPoint m_Model_Center;                   // stlģ�����ĵ�����
	QSTLPoint m_fRotationValue;                 // stlģ����ת�Ƕ�

	//��������
public:
	// ���stlģ�Ͳ���
	void Clear();

	// ��ȡģ�Ͷ�Ӧ������λ������ļ�ֵ(isMin = trueΪ��ȡģ��λ�õ���Сֵ, isMin = falseΪ��ȡģ��λ�õ����ֵ)
	float GetModelAxisPos(AxisId nAxes, bool isMin);

	// ��ȡģ������ļ�ֵ(isMin = trueΪ��ȡģ��λ�õ���Сֵ, isMin = falseΪ��ȡģ��λ�õ����ֵ)
	QSTLPoint GetModelPos(bool isMin);

	// ��ȡģ�ͳߴ�
	QSTLPoint GetModelSize(void);

	// ��ȡģ�����ĵ�����
	QSTLPoint GetModelCenter(void);

	// ��ȡģ����ת�Ƕ�
	QSTLPoint GetModelRotation(void);

	// ���¼���ģ��ÿ����ĵ�λ������
	void ReCalNormal(void);

	// д����
	void WriteArchive(QFile& archive);

	// ����stl�ļ�
	void LoadSTL();

	//�����߳̿��� �������߳� ����stl�ļ�
	bool BeginThread();

	// �ж��Ƿ����m_strPathName_STLָ����stl�ļ�
	bool isStlLoadAble();

	inline void SetWnd(HWND hWnd) { m_hNotifyWnd = hWnd; }

	// ������Ҫ���ص�stl�ļ���
	inline void SetPathName_STL(QString str) { m_strPathName_STL = str; }

	//[����]		������Ҫ���ص�GCode�ļ���
	inline void SetPathName_GCode(QString str) { m_strPathName_GCode = str; }

	//[����]		��ȡ���ص�stl�ļ���
	inline QString GetPathName_STL() { return m_strPathName_STL; }

	//[����]		��ȡ���ص�stl�ļ������������
	inline STLFaceArray& GetStlFaces() { return m_faces; }

	//[����]		��ȡ���ص�stl�ļ��ĵ��������
	inline STLPointArray& GetStlPoints() { return m_points; }

	//[����]		�ж��Ƿ��Ѽ���stl�ļ�
	inline bool isStlLoaded() { return m_StlLoadState == STATE_STL_LOADED; }

	//�߳��Ƿ�����
	//inline bool IsThreadRunning() { return m_hThreadHandle != NULL; }

	////����߳̾��
	//inline HANDLE GetThread() { return m_hThreadHandle; }

	////��ͣ�����߳�
	//inline bool SuspendThread(){ return IsThreadRunning() ? ::SuspendThread(m_hThreadHandle) != 0xFFFFFFFF : false; }

	////�ָ������߳�
	//inline bool ResumeThread() { return IsThreadRunning() ? ::ResumeThread(m_hThreadHandle) != 0xFFFFFFFF : false; }

	////��ֹ�߳�
	//bool EndThread(DWORD dwWaitTime = 100);

	// ģ��ƽ��
	void AxesMove(AxisId axes, float movedlength);

	// �ƶ���ƽ̨
	void MovetoPlateform();

	// �ƶ�������(Z�ᱣ�ֲ���)
	void MovetoCenter();

	// ��ת����������ʱ��ģ��
	void OnRotation(AxisId axes, float fRotationValue);

	// ��������ģ��
	void OnScale(float fScaleValue);

	// ����ģ�Ͷ�Ӧ��ߴ�
	void OnScale(AxisId axes, float fScaleValue);

	// ����stl�㡢������
	void ModelBackUp();

	// ��ԭ��֮ǰ�����ģ��
	void ModelRestore();

	// ��ȡstlģ�͵ĳߴ�
	void CalQModelSize();

	// �ж�ģ���Ƿ��޸�
	bool IsModelChanged();

	// ����ģ��Ϊ�ѱ���(��ģ�����޸ı�־��Ϊfalse)
	void SetFileSaved();
private:
	// ���ASCII��STL�ļ����ؼ���
	static bool	ReadKeyword(istream& istream, const char* keyword);

	// �ж�STL�ļ������Ƿ�ΪASCII��ʽ
	static bool IsAsciiStlFile(ifstream& ifstream, long& filePtr);

	// ���������Сֵ(ͨ�������޸���ֵ)
	static void SetMinMaxVal(float val, float& min, float& max);

	// ���������Сֵ(ͨ������ָ���޸���ֵ)
	static void SetMinMaxVal(float val, float* min, float* max);

	// ������Ϣ֪ͨӦ�ó���stl����״̬�Ѹ���
	static void SetCurrState(QSTLSolid* pThreadInfo, STL_LOAD_STATE state);

	// ������Ϣ֪ͨӦ�ó���stl���ؽ����Ѹ���
	static void SetCurrPos(QSTLSolid* pThreadInfo, int nPos);

	// ���ؽ���ʱ����ϵͳ�¼�
	void DoEvent();

	// ����stl�ļ��̺߳���
	//static DWORD WINAPI ThreadProc_StlLoad(LPVOID lpPara);
public:
	// �ж�ģ���Ƿ��ڴ�ӡ������
	bool IsModelInMachine(int nBuildSize_X, int nBuildSize_Y, int nBuildSize_Z);

	// ����ģ�Ͷ�Ӧ��GCode������Ϣ
	void LoadGCodeConfig(QString FileName);

	// ����ģ�Ͷ�Ӧ��GCode������Ϣ
	void SaveGCodeConfig(QString FileName);

	// ��ȡģ�Ͷ�Ӧ��GCode������Ϣ
	//CGCodeConfig* GetGCodeConfig();
};

