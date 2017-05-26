#pragma once
#include <QThread>
#include "GlobleDefine.h"
#include <QMap>
#include <QVector>
#include <QList>
#include <QDebug>
#include <QMutex>

//������ͷ��ṹ��
struct OneNozzleStore
{
	bool	ISEXIST;
	NozzleType	TYPE;
	int	STOREROOM;
	bool	USING;
	float	TEMP;
	bool	ISCONTROLTEMP;
	bool	ISCALIBRATED;
};

class QNozzleInfo : public QThread
{
	Q_OBJECT

public:
	QNozzleInfo(QObject *parent);
	~QNozzleInfo();
public:
	QMap<NozzleStoreRoom,OneNozzleStore> m_NozzleStore;
public slots:
	void slotUpdataNozzleInfo(QByteArray info);
	void slotUpdataNozzleTemp(QByteArray info);
	
protected:

	RetNozzle Init(void);
	//RetNozzle GetAllNozzleID(QList<int> listNozzleID);
	//RetNozzle GetUsingNzoole(OneNozzle);
	//RetNozzle GetOneNozzleTemp(int id, float temp);
	//RetNozzle GetOneNozzleTemp(QString guid, float temp);
	//
	//bool IsExist(NozzleStoreRoom);

	//RetNozzle AddOneNozzle(int id, OneNozzle nozzle);//����ID

	//RetNozzle RemoveOneNozzle(QString guid);
	//RetNozzle RemoveOneNozzle(int id);

	//RetNozzle ChangeUsingNozzle(int id);
	//RetNozzle ChangeUsingNozzle(QString guid);

	//RetNozzle NozzleSetTemp(int id);
	//RetNozzle NozzleSetTemp(QString guid);
signals:
	void signalNozzleStoreToWidget(QMap<NozzleStoreRoom, OneNozzleStore>);
};
