#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BioPrint.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>

#include "QModelView.h"
#include "QMachineWidget.h"
#include "QMachinePTWidget.h"
#include "QMySerialPort.h"
#include "QNozzleInfo.h"


#include "QSystemConfig.h"

class BioPrint : public QMainWindow
{
	Q_OBJECT

public:
	BioPrint(QWidget *parent = Q_NULLPTR);
	~BioPrint();
protected slots:
	void setModelWidget(void);
	void setProjectWidget(void);
	void myslot(void);
private:
	Ui::BioPrintClass ui;

	void InitWidget(void);
private:
	QMachineWidget *m_QMachineWidget;
	QMachinePTWidget *m_QMachinePTWidget;
	QModelView *m_QModelView;
	QMySerialPort *m_QMySerialPort;
	QNozzleInfo *m_QNozzleInfo;
	//���ӽ���
	QPushButton *m_ConnectMachine;
	QPushButton *m_ConnectSetup;
	//�豸������Ϣ
	QLabel *m_WaterFlow;
	QLabel *m_GasPa;
	QLabel *m_TempPlat;
	//��ͷ��Ϣ
	QPushButton *PT1;
	QPushButton *PT2;
	QPushButton *PT3;
	QPushButton *PT4;
	//��ͷ����
	bool flag;
};
