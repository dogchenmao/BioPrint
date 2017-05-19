#include "QMySerialPort.h"

QMutex mutex;

void QMySerialPort::showAllSerialPort()
{
	//foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	//{
	//	qDebug() << "Name : " << info.portName();
	//	serialSet(m_serial,info.portName(), QSerialPort::Baud115200, QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop);
	//	m_serial->open(QIODevice::ReadWrite);
	//	m_serial->write("");
	//	m_serial->write("");
	//}
}

QMySerialPort::QMySerialPort(QObject *parent)
: QThread(parent)
{
	m_bFindSerialPort = false;
	m_SerialReadBuff.clear();
	m_SerialInsBuff.clear();


	m_serial = new QSerialPort(this);
	connect(m_serial, &QIODevice::readyRead, this, &QMySerialPort::serialRead);
	serialSet(m_serial, "COM10", QSerialPort::Baud115200, QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop);
	//showAllSerialPort();
	serialOpen();
	
}

QMySerialPort::~QMySerialPort()
{

}

void QMySerialPort::run()
{
	//ito = new InThreadObject;
	//	// ע�����������ʹ����QT::BlockingQueuedConnectionѡ��
	//	connect(ito,
	//	&InThreadObject::request,
	//	pMainWindow,
	//	&MainWindow::response,
	//	QT::BlockingQueuedConnection);
	//	// ͬ����ȡ�������ֵ
	//	QVariant var;
	//ito->request("param.level", var);
	//// �����ͬ���ȴ����߳�ִ��response������
	//int param = var.toInt();
}


bool QMySerialPort::serialSet(QSerialPort *serialport,const QString serialname,	const qint32 baudrate,	QSerialPort::DataBits databit,	QSerialPort::Parity parity,	QSerialPort::StopBits stopbits)
{
	if (!serialport->isOpen())
	{
		serialport->setPortName(serialname);
		serialport->setBaudRate(baudrate);
		serialport->setDataBits(databit);
		serialport->setParity(parity);
		serialport->setStopBits(stopbits);
		return true;
	}
	return false;
}

void QMySerialPort::serialOpen()
{
	if (!m_serial->isOpen())
	{
		if (m_serial->open(QIODevice::ReadWrite))
		{
			qDebug() << "SerialPort is Opened";
		}
	}
}

void QMySerialPort::serialRead()
{
	mutex.lock();

	//��ȡ���д�������
	QByteArray data = m_serial->readAll();
	m_SerialReadBuff.append(data);

	//�Ի��зָ�����
	QList<QByteArray> ins_list = m_SerialReadBuff.split('\n');

	//�ֱ���ÿ������
	for (int i = 0; i < ins_list.length(); i++)
	{
		char ins_start;
		m_SerialInsBuff.clear();

		if (ins_list[i].endsWith('\r') && (ins_list[i].length() >= 3))
		{
			//�ҵ���һ��#
			ins_start = ins_list[i].lastIndexOf('#');
			if (ins_start != -1)
			{
				m_SerialInsBuff = ins_list[i].remove(1, ins_start);
				m_SerialInsBuff.chop(1);
				if (m_SerialInsBuff.mid(0, 14) == "#GET_PT_STATUS")
				{
					emit signalUpdataNozzleInfo(m_SerialInsBuff.mid(15));
				}
				if (m_SerialInsBuff.mid(0, 13) == "#TEMP_GET_ALL")
				{
					emit signalUpdataNozzleTemp(m_SerialInsBuff.mid(14));
				}
				if (m_SerialInsBuff.mid(0, 9) == "#SPEED_1_")
				{
					emit signalUpdataChilleInfo(m_SerialInsBuff.mid(10));
				}
				if (m_SerialInsBuff.mid(0, 9) == "#SPEED_2_")
				{

				}
			}

		}

	}
	m_SerialReadBuff.clear();
	m_SerialReadBuff.append(ins_list.takeLast());

	mutex.unlock();
}

void QMySerialPort::serialWrite(const char *ins)
{
	if (m_serial->isWritable())
	{
		mutex.lock();
		m_serial->write(ins);
		mutex.unlock();
	}
}
