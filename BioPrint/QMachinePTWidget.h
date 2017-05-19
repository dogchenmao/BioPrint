#pragma once

#include <QWidget>
#include "ui_QMachinePTWidget.h"
#include <QLayout>
#include <QPushButton>
#include <QMap>
#include "GlobleDefine.h"

class QMachinePTWidget : public QWidget
{
	Q_OBJECT

public:
	QMachinePTWidget(QWidget *parent = Q_NULLPTR);
	~QMachinePTWidget();
protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void timerEvent(QTimerEvent *event);
private:
	Ui::QMachinePTWidget ui;
	uint m_NozzleTotal;

	//修改喷头类型
	void m_SetType(uint NozzleIndex, NozzleType type);	

	bool mybool;
};
