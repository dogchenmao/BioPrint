#pragma once

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QMutex>
#include <QDebug>
#include <QThread>
#include "GlobleDefine.h"

class QMySerialPort : public QThread
{
	Q_OBJECT
private:
	QSerialPort *m_serial;
	bool m_bFindSerialPort;
	QByteArray m_SerialReadBuff;
	QByteArray m_SerialInsBuff;

	//flag bit
	bool m_isGetTemp;
	bool m_isGetPtStatus;
	bool m_isGetPressure;
	bool m_isGetFlowSpeed;
protected:
	void getOneIns(QByteArray buff);
	void init(void);

protected:
	virtual void run();
	virtual void timerEvent(QTimerEvent *event);
public:
	QMySerialPort(QObject *parent);
	~QMySerialPort();
	
	void showAllSerialPort();
	bool serialSet(QSerialPort *serialport,
		const QString serialname,
		const qint32 baudrate,
		QSerialPort::DataBits databit,
		QSerialPort::Parity parity, 
		QSerialPort::StopBits stopbits);
	void serialOpen();
signals:
	void signalUpdataNozzleInfo(QByteArray info);
	void signalUpdataNozzleTemp(QByteArray temp);
	void signalUpdataChilleInfo(QByteArray info);
public slots:
	void serialRead();
	bool serialWrite(const char *ins);


};
