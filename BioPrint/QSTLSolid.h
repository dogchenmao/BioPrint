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

typedef QVector<QSTLPoint> STLPointArray;        // QSTLPoint类型的数组
typedef QVector<QSTLFace> STLFaceArray;           // CSTLFace类型的数组

// stl文件加载状态
enum STL_LOAD_STATE
{
	STATE_STL_LOADING = STL_LOADING,           // 加载中
	STATE_STL_RECONSTRUCT = STL_RECONSTRUCT,           // 重建中
	STATE_STL_LOADED = STL_LOADED,		    // 已加载
	STATE_STL_UNLOAD = STL_UNLOAD,		    // 未加载
	STATE_STL_LOADFAILED = STL_LOADFAILED,           // 加载失败
};

// stl模型类
class QSTLSolid : public QThread
{
	Q_OBJECT
public:
	QSTLSolid(QObject *parent = Q_NULLPTR);
	~QSTLSolid(void);
	const QSTLSolid& operator=(const QSTLSolid&);
private:
	void run();
	//内部属性
private:
	HWND m_hNotifyWnd;                          // stl模型类句柄
	STL_LOAD_STATE m_StlLoadState;              // stl文件加载状态
	QString m_strPathName_STL;                  // stl文件名(包含路径)
	QString m_strPathName_GCode;                // GCode文件名(包含路径)
	volatile bool m_fRunFlag;		            // 线程运行标志

	STLPointArray m_points;						// stl文件中点参数阵列
	STLFaceArray m_faces;						// stl文件中面参数阵列(1个面由3个点组成)
	STLPointArray m_points_backup;			    // stl文件中点数据备份
	STLFaceArray m_faces_backup;			    // stl文件中面数据备份(1个面由3个点组成)
	float m_xMin;                               // stl模型x轴最小坐标
	float m_xMax;                               // stl模型x轴最大坐标
	float m_yMin;                               // stl模型y轴最小坐标
	float m_yMax;                               // stl模型y轴最大坐标
	float m_zMin;                               // stl模型z轴最小坐标
	float m_zMax;                               // stl模型z轴最大坐标
	bool m_isModelChanged;                      // 模型是否被修改

	QSTLPoint m_Model_Center;                   // stl模型中心点坐标
	QSTLPoint m_fRotationValue;                 // stl模型旋转角度

	//公开方法
public:
	// 清空stl模型参数
	void Clear();

	// 获取模型对应轴所在位置坐标的极值(isMin = true为获取模型位置的最小值, isMin = false为获取模型位置的最大值)
	float GetModelAxisPos(AxisId nAxes, bool isMin);

	// 获取模型坐标的极值(isMin = true为获取模型位置的最小值, isMin = false为获取模型位置的最大值)
	QSTLPoint GetModelPos(bool isMin);

	// 获取模型尺寸
	QSTLPoint GetModelSize(void);

	// 获取模型中心点坐标
	QSTLPoint GetModelCenter(void);

	// 获取模型旋转角度
	QSTLPoint GetModelRotation(void);

	// 重新计算模型每个面的单位法向量
	void ReCalNormal(void);

	// 写入流
	void WriteArchive(QFile& archive);

	// 加载stl文件
	void LoadSTL();

	//辅助线程控制 建监视线程 加载stl文件
	bool BeginThread();

	// 判断是否存在m_strPathName_STL指定的stl文件
	bool isStlLoadAble();

	inline void SetWnd(HWND hWnd) { m_hNotifyWnd = hWnd; }

	// 设置需要加载的stl文件名
	inline void SetPathName_STL(QString str) { m_strPathName_STL = str; }

	//[功能]		设置需要加载的GCode文件名
	inline void SetPathName_GCode(QString str) { m_strPathName_GCode = str; }

	//[功能]		获取加载的stl文件名
	inline QString GetPathName_STL() { return m_strPathName_STL; }

	//[功能]		获取加载的stl文件的面参数阵列
	inline STLFaceArray& GetStlFaces() { return m_faces; }

	//[功能]		获取加载的stl文件的点参数阵列
	inline STLPointArray& GetStlPoints() { return m_points; }

	//[功能]		判断是否已加载stl文件
	inline bool isStlLoaded() { return m_StlLoadState == STATE_STL_LOADED; }

	//线程是否运行
	//inline bool IsThreadRunning() { return m_hThreadHandle != NULL; }

	////获得线程句柄
	//inline HANDLE GetThread() { return m_hThreadHandle; }

	////暂停监视线程
	//inline bool SuspendThread(){ return IsThreadRunning() ? ::SuspendThread(m_hThreadHandle) != 0xFFFFFFFF : false; }

	////恢复监视线程
	//inline bool ResumeThread() { return IsThreadRunning() ? ::ResumeThread(m_hThreadHandle) != 0xFFFFFFFF : false; }

	////终止线程
	//bool EndThread(DWORD dwWaitTime = 100);

	// 模型平移
	void AxesMove(AxisId axes, float movedlength);

	// 移动到平台
	void MovetoPlateform();

	// 移动到中心(Z轴保持不变)
	void MovetoCenter();

	// 旋转沿坐标轴逆时针模型
	void OnRotation(AxisId axes, float fRotationValue);

	// 整体缩放模型
	void OnScale(float fScaleValue);

	// 缩放模型对应轴尺寸
	void OnScale(AxisId axes, float fScaleValue);

	// 备份stl点、面数据
	void ModelBackUp();

	// 还原到之前保存的模型
	void ModelRestore();

	// 获取stl模型的尺寸
	void CalQModelSize();

	// 判断模型是否被修改
	bool IsModelChanged();

	// 设置模型为已保存(将模型已修改标志置为false)
	void SetFileSaved();
private:
	// 检测ASCII型STL文件流关键字
	static bool	ReadKeyword(istream& istream, const char* keyword);

	// 判断STL文件类型是否为ASCII形式
	static bool IsAsciiStlFile(ifstream& ifstream, long& filePtr);

	// 设置最大、最小值(通过引用修改最值)
	static void SetMinMaxVal(float val, float& min, float& max);

	// 设置最大、最小值(通过传递指针修改最值)
	static void SetMinMaxVal(float val, float* min, float* max);

	// 发送消息通知应用程序stl加载状态已更改
	static void SetCurrState(QSTLSolid* pThreadInfo, STL_LOAD_STATE state);

	// 发送消息通知应用程序stl加载进度已更新
	static void SetCurrPos(QSTLSolid* pThreadInfo, int nPos);

	// 加载进程时处理系统事件
	void DoEvent();

	// 加载stl文件线程函数
	//static DWORD WINAPI ThreadProc_StlLoad(LPVOID lpPara);
public:
	// 判断模型是否在打印区域内
	bool IsModelInMachine(int nBuildSize_X, int nBuildSize_Y, int nBuildSize_Z);

	// 加载模型对应的GCode配置信息
	void LoadGCodeConfig(QString FileName);

	// 保存模型对应的GCode配置信息
	void SaveGCodeConfig(QString FileName);

	// 获取模型对应的GCode配置信息
	//CGCodeConfig* GetGCodeConfig();
};

