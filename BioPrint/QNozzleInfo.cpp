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
	if (!info.isEmpty())
	{
		OneNozzle oneNozzleBuff;

		switch (static_cast<int>(info[3]))
		{
		case NozzleCold:
			oneNozzleBuff.TYPE = NozzleCold;
			break;
		case NozzleHot:
			oneNozzleBuff.TYPE = NozzleHot;
			break;
		case NozzleNormal:
			oneNozzleBuff.TYPE = NozzleNormal;
			break;
		case NozzleNull:
			oneNozzleBuff.TYPE = NozzleNull;
			break;
		default:
			break;
		}
		oneNozzleBuff.STOREROOM = 1;
		oneNozzleBuff.ID;
		//git test
	}
	else
	{
		//do nothing
	}
}