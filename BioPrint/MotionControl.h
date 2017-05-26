#pragma once
#include <QObject>
#include <QThread>
#include "mc_config.h"
#include "mc_com_udcs.h"
#include "mc_gstr.h"
#include <QVector>

class MotionControl : public QThread
{
	Q_OBJECT
private:
	volatile bool		m_ThreadRun;		             //!< 是否开始线程
	volatile bool		m_ConnectState;					//!< 运动控制器连接状态
	volatile bool		m_HardFault;					//!< 是否有错误
	volatile bool		m_PackageRunFlag;              //!< 是否有数据需要发送标志
	QVector<QString>	m_PackageArray;                 //!< 待发送指令列表

public:
	MotionControl(QObject *parent);
	~MotionControl();
	void Close();
	void ClearSendPackage(void);
	void SendPackage(QVector<QString>& PackageArray);
	void SendImmediatePackage(QVector<QString>& ImmediatePackageArray);
private:
	void Init();
protected:
	virtual void run();
};

