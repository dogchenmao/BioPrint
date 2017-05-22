#include "QNozzleInfo.h"

QMutex nmutex;

QNozzleInfo::QNozzleInfo(QObject *parent)
	: QThread(parent)
{
	Init();
}

QNozzleInfo::~QNozzleInfo()
{
}

RetNozzle QNozzleInfo::Init(void)
{
	OneNozzleStore oneNozzleBuff;
	for (int i = NozzleStoreRoomA; i <= NozzleStoreRoomD; i++)
	{
		oneNozzleBuff.ISCALIBRATED = false;
		oneNozzleBuff.ISCONTROLTEMP = false;
		oneNozzleBuff.ISEXIST = false;
		oneNozzleBuff.STOREROOM = static_cast<NozzleStoreRoom>(i);
		oneNozzleBuff.TEMP = 0;
		oneNozzleBuff.TYPE = NozzleTypeNull;
		oneNozzleBuff.USING = false;
		m_NozzleStore.insert(static_cast<NozzleStoreRoom>(i), oneNozzleBuff);
	}
	return SUCCESS;
}
void QNozzleInfo::slotUpdataNozzleInfo(QByteArray info)
{
	nmutex.lock();

	QVector<NozzleType> Info;
	if (info.length() < PT_MAX_COUNT * 2 || info.isNull())
	{//�ж�info���յ�������������
		return ;
	}
	else
	{//��infoת��Ϊö������洢
		Info.clear();
		for (size_t nozzlstore = 0; nozzlstore <= PT_MAX_COUNT; nozzlstore++)		//nozzlstore��0��PT_MAX_COUNT�����ʾ��ͷ���Ϲ���
		{
			int nozzlebuff = info[nozzlstore*2 + 1] - '0' ;				//2*i+1�ֱ�ȡ_0_0_0_0_0�е���ͷ��Ϣ
			Info.push_back(static_cast<NozzleType>(nozzlebuff));				//������ֵ�������ͷ������Ϣ
		}
	}
	
	if (Info.size() != PT_MAX_COUNT+1)
	{//�ж�Info��С����ֹ����
		return;
	}

	for (size_t i = 1; i < Info.size(); i++)
	{//���θ�����ͷ����Ϣ
		m_NozzleStore[static_cast<NozzleStoreRoom>(i)].ISEXIST = (Info[i] == NozzleTypeNull) ? false : true;

		if (m_NozzleStore[static_cast<NozzleStoreRoom>(i)].ISEXIST)
		{
			m_NozzleStore[static_cast<NozzleStoreRoom>(i)].TYPE = Info[i];
		}
		else
		{
			m_NozzleStore[static_cast<NozzleStoreRoom>(i)].TYPE = NozzleTypeNull;
		}

		m_NozzleStore[static_cast<NozzleStoreRoom>(i)].STOREROOM = static_cast<NozzleStoreRoom>(i);

		m_NozzleStore[static_cast<NozzleStoreRoom>(i)].USING = false;

	}
	if (Info[0] != NozzleTypeNull)
	{//������ͷ������ͷ��Ϣ,��䵽��һ����λ
		QMap<NozzleStoreRoom, OneNozzleStore>::iterator it;
		for (it = m_NozzleStore.begin(); it != m_NozzleStore.end(); ++it)
		{
			if (!it.value().ISEXIST)
			{
				m_NozzleStore[it.key()].ISEXIST = true;
				m_NozzleStore[it.key()].TYPE = Info[0];
				m_NozzleStore[it.key()].STOREROOM = it.key();
				m_NozzleStore[it.key()].USING = true;
				break;
			}
		}
	}
	//������ʾ�ź�
	emit signalNozzleStoreToWidget(m_NozzleStore);

	nmutex.unlock();

}

void QNozzleInfo::slotUpdataNozzleTemp(QByteArray info)
{
	QList<QByteArray> baList = info.split('_');
	
	for (size_t i = 1; i < baList.size(); i++)
	{
		qDebug()<<baList[i].toFloat();
	}
}