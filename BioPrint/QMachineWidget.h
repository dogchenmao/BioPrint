#pragma once

#include <QWidget>
#include "ui_QMachineWidget.h"

#include "GlobleDefine.h"
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QRadioButton>

class QMachineWidget : public QWidget
{
	Q_OBJECT

public:
	QMachineWidget(QWidget *parent = Q_NULLPTR);
	~QMachineWidget();
private:
	bool	m_isMoveContinu;
	float	m_MoveLength;
	float	m_MoveSpeedXY;
	float	m_MoveSpeedZ;
	float	m_Pressure;

signals:

protected slots:
	
private:
	//≥ı ºªØ¥∞ÃÂ
	void initWidget(void);
private:
	Ui::QMachineWidget ui;
};
