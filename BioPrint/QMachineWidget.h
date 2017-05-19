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
	QLabel* m_labelCurrentPt;
	QLabel* m_labelChangePt;
	QLabel* m_labelMoveModel;
	QRadioButton* m_radioMoveContinue;
	QRadioButton* m_radioMoveFix;
	QLabel* m_labelMoveDistance;
	QRadioButton* m_radioMoveOneMM;
	QRadioButton* m_radioMoveDeciMM;
	QRadioButton* m_radioMoveCustomMM;
	QLabel* m_labelShowMM;

signals:

protected slots:
	
private:
	//≥ı ºªØ¥∞ÃÂ
	void initWidget(void);
private:
	Ui::QMachineWidget ui;
};
