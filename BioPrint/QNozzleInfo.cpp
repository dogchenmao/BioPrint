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
	{//判断info接收到的数据完整性
		return ;
	}
	else
	{//将info转换为枚举数组存储
		Info.clear();
		for (size_t nozzlstore = 0; nozzlstore <= PT_MAX_COUNT; nozzlstore++)		//nozzlstore从0至PT_MAX_COUNT，零表示喷头臂上挂载
		{
			int nozzlebuff = static_cast<int>(info[nozzlstore*2 + 1]) - 48;				//2*i+1分别取_0_0_0_0_0中的喷头信息
			Info.push_back(static_cast<NozzleType>(nozzlebuff));				//往返回值中添加喷头类型信息
		}
	}
	
	if (Info.size() != PT_MAX_COUNT+1)
	{//判断Info大小，防止出错
		return;
	}

	for (size_t nozzlstore = 1; nozzlstore < Info.size(); nozzlstore++)
	{
		if (Info.at(nozzlstore) != NozzleNull)//1取_H_A_B_C_D中的喷头信息中H位
		{//喷头臂已挂载喷头
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
	//for (size_t nozzlstore = 0; nozzlstore <= PT_MAX_COUNT; nozzlstore++)	//nozzlstore从0至PT_MAX_COUNT，零表示喷头臂上挂载
	//{
	//	OneNozzle oneNozzleBuff;

	//	switch (static_cast<int>(info[nozzlstore + 1]))		//i+1分别取_0_0_0_0_0中的喷头信息
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
	//	{//新挂载喷头，喷头对应刀座信息缺失

	//	}
	//	else
	//	{
	//		oneNozzleBuff.STOREROOM = nozzlstore;
	//	}
	//	//git test
}