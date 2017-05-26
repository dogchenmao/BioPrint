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
	volatile bool		m_ThreadRun;		             //!< �Ƿ�ʼ�߳�
	volatile bool		m_ConnectState;					//!< �˶�����������״̬
	volatile bool		m_HardFault;					//!< �Ƿ��д���
	volatile bool		m_PackageRunFlag;              //!< �Ƿ���������Ҫ���ͱ�־
	QVector<QString>	m_PackageArray;                 //!< ������ָ���б�

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

