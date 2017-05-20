#pragma once
#include <QThread>
#include "GlobleDefine.h"
#include <QMap>
#include <QVector>
#include <QList>
#include <QDebug>
//喷头信息结构体
struct OneNozzle
{
	int	ID;
	QString	GUID;
	NozzleType	TYPE;
	int	STOREROOM;
	bool	USING;
	float	TEMP;
};

class QNozzleInfo : public QThread
{
	Q_OBJECT

public:
	QNozzleInfo(QObject *parent);
	~QNozzleInfo();
private:
	QMap <int, OneNozzle> NozzleStore;
	QMap <int, OneNozzle> PreNozzleStore;
public slots:
	void slotUpdataNozzleInfo(QByteArray info);
protected:

	RetNozzle Init(void);
	RetNozzle GetAllNozzleID(QList<int> listNozzleID);
	RetNozzle GetUsingNzoole(OneNozzle);
	RetNozzle GetOneNozzleTemp(int id, float temp);
	RetNozzle GetOneNozzleTemp(QString guid, float temp);
	
	bool IsExist(NozzleStoreRoom);

	RetNozzle AddOneNozzle(int id, OneNozzle nozzle);//返回ID

	RetNozzle RemoveOneNozzle(QString guid);
	RetNozzle RemoveOneNozzle(int id);

	RetNozzle ChangeUsingNozzle(int id);
	//RetNozzle ChangeUsingNozzle(QString guid);

	//RetNozzle NozzleSetTemp(int id);
	//RetNozzle NozzleSetTemp(QString guid);

};
