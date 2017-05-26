#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BioPrint.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>

#include "MotionControl.h"
#include "QModelView.h"
#include "QMachineWidget.h"
#include "QMachinePTWidget.h"
#include "QMySerialPort.h"
#include "QNozzleInfo.h"
#include "QTitleWidget.h"
#include "QMainMenu.h"
#include "QSystemConfig.h"
#include "QSystemTray.h"

class BioPrint : public QMainWindow
{
	Q_OBJECT

public:
	BioPrint(QWidget *parent = Q_NULLPTR);
	~BioPrint();
protected slots:
	void setModelWidget(void);
	void setProjectWidget(void);
	void showMainMenu(void);
	void showMax(void);
protected:
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);
private:
	Ui::BioPrintClass ui;
	void InitWidget(void);
	void ConnectSignalSlot(void);
public:
	QMachineWidget *m_QMachineWidget;
	QMachinePTWidget *m_QMachinePTWidget;
	QModelView *m_QModelView;
	QMySerialPort *m_QMySerialPort;
	QNozzleInfo *m_QNozzleInfo;
	QTitleWidget *m_QTitleWidget;
	QMainMenu *m_QMainMenu;
	QSystemTray * m_QSystemTray;
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

	//�˶�������
	MotionControl *m_MotionControl;

	QRect location;
};
