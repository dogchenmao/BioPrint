#include "QNozzleInfo.h"

QNozzleInfo::QNozzleInfo(QObject *parent)
	: QThread(parent)
{
}

QNozzleInfo::~QNozzleInfo()
{
}

RetNozzle QNozzleInfo::Init(void)
{
	NozzleStore.clear();
	return SUCCESS;
}

RetNozzle QNozzleInfo::GetAllNozzleID(QList<int> listNozzleID)
{
	if (!NozzleStore.isEmpty())
	{
		listNozzleID.clear();
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			listNozzleID.append(it.key());
		}
		return SUCCESS;
	}
	return NONE;
}

RetNozzle QNozzleInfo::GetUsingNzoole(OneNozzle oneNozzle)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.value().USING)
			{
				oneNozzle = it.value();
				return SUCCESS;
			}
			return NONE;
		}
	}
	return NONE;
}

RetNozzle QNozzleInfo::GetOneNozzleTemp(int id, float temp)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.key() == id)
			{
				temp = it.value().TEMP;
				return SUCCESS;
			}
			return FAIL;
		}
	}
	return NONE;
}
RetNozzle QNozzleInfo::GetOneNozzleTemp(QString guid, float temp)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.value().GUID == guid)
			{
				temp = it.value().TEMP;
				return SUCCESS;
			}
			return FAIL;
		}
	}
	return NONE;
}

bool QNozzleInfo::IsExist(NozzleStoreRoom storeroom)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.value().STOREROOM == storeroom)
			{
				return true;
			}
		}
	}
	return false;
}

RetNozzle QNozzleInfo::AddOneNozzle(int id, OneNozzle nozzle)
{
	QMap <int, OneNozzle>::iterator it;
	for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
	{
		if (it.key() == id)
		{
			return FAIL;
		}
	}
	NozzleStore.insert(id,nozzle);
	return SUCCESS;
}

RetNozzle QNozzleInfo::RemoveOneNozzle(int id)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.value().ID == id)
			{
				NozzleStore.erase(it);
				return SUCCESS;
			}
			return NONE;
		}
	}
	return FAIL;
}

RetNozzle QNozzleInfo::ChangeUsingNozzle(int id)
{
	if (!NozzleStore.isEmpty())
	{
		QMap <int, OneNozzle>::iterator it;
		for (it = NozzleStore.begin(); it != NozzleStore.end(); ++it)
		{
			if (it.value().USING)
			{
				it.value().USING = false;
			}
			return NONE;
		}
		NozzleStore[id].USING = true;
	}
	return FAIL;
}

void QNozzleInfo::slotUpdataNozzleInfo(QByteArray info)
{

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
			int nozzlebuff = static_cast<int>(info[nozzlstore*2 + 1]) - 48;				//2*i+1�ֱ�ȡ_0_0_0_0_0�е���ͷ��Ϣ
			Info.push_back(static_cast<NozzleType>(nozzlebuff));				//������ֵ�������ͷ������Ϣ
		}
	}
	
	if (Info.size() != PT_MAX_COUNT+1)
	{//�ж�Info��С����ֹ����
		return;
	}

	for (size_t nozzlstore = 1; nozzlstore < Info.size(); nozzlstore++)
	{
		if (Info.at(nozzlstore) != NozzleNull)//1ȡ_H_A_B_C_D�е���ͷ��Ϣ��Hλ
		{//��ͷ���ѹ�����ͷ
			if (!IsExist(static_cast<NozzleStoreRoom>(nozzlstore)))
			{
				OneNozzle oneNozzleBuff;
				int id = NozzleStore.size() + 1;
				oneNozzleBuff.ID = id;
				oneNozzleBuff.STOREROOM = static_cast<NozzleStoreRoom>(nozzlstore);
				oneNozzleBuff.TYPE = Info.at(nozzlstore);
				oneNozzleBuff.USING = false;
				AddOneNozzle(id,oneNozzleBuff);
			}
		}
	}
	NozzleStore.size();
	//for (size_t nozzlstore = 0; nozzlstore <= PT_MAX_COUNT; nozzlstore++)	//nozzlstore��0��PT_MAX_COUNT�����ʾ��ͷ���Ϲ���
	//{
	//	OneNozzle oneNozzleBuff;

	//	switch (static_cast<int>(info[nozzlstore + 1]))		//i+1�ֱ�ȡ_0_0_0_0_0�е���ͷ��Ϣ
	//	{
	//	case NozzleCold:
	//		oneNozzleBuff.TYPE = NozzleCold;
	//		break;
	//	case NozzleHot:
	//		oneNozzleBuff.TYPE = NozzleHot;
	//		break;
	//	case NozzleNormal:
	//		oneNozzleBuff.TYPE = NozzleNormal;
	//		break;
	//	case NozzleNull:
	//		oneNozzleBuff.TYPE = NozzleNull;
	//		break;
	//	default:
	//		break;
	//	}
	//	if (oneNozzleBuff.STOREROOM == 0)
	//	{//�¹�����ͷ����ͷ��Ӧ������Ϣȱʧ

	//	}
	//	else
	//	{
	//		oneNozzleBuff.STOREROOM = nozzlstore;
	//	}
	//	//git test
}