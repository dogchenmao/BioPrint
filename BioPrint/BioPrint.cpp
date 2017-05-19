#include "BioPrint.h"
#include <QtWidgets/QOpenGLWidget>


BioPrint::BioPrint(QWidget *parent)
: QMainWindow(parent), flag(false)
{
	ui.setupUi(this);


	m_QMySerialPort = new QMySerialPort(this);

	m_QNozzleInfo = new QNozzleInfo(this);
	QObject::connect(m_QMySerialPort, SIGNAL(signalUpdataNozzleInfo(QByteArray)), m_QNozzleInfo, SLOT(slotUpdataNozzleInfo(QByteArray)));

	//InitWidget();
	m_QMachinePTWidget = new QMachinePTWidget(this);
	ui.LeftLayout_D_U->addWidget(m_QMachinePTWidget);
	m_QMachinePTWidget->show();

	m_QMachineWidget = new QMachineWidget;
	ui.LeftLayout_U->addWidget(m_QMachineWidget);
	m_QMachineWidget->show();

	m_QModelView = new QModelView;
	ui.RightLayout_L_U->addWidget(m_QModelView);
	m_QModelView->show();

	QSystemConfig myApp;
	QDir aa;
	QString IniFile;
	IniFile = aa.currentPath() + "/Inis/SystemSetting.ini";
	aa.currentPath();
	myApp.SetFileName(&IniFile);
	myApp.Load();

	m_QMySerialPort->serialWrite(IniFile.toLatin1().data());
}
BioPrint::~BioPrint()
{
	
}
void BioPrint::setModelWidget()
{

}
void BioPrint::setProjectWidget()
{

}
void BioPrint::myslot()
{
	if (!flag)
	{
		m_QMachineWidget->hide();
		flag = true;
	}
	else
	{
		m_QMachineWidget->show();
		flag = false;
	}

}
void BioPrint::InitWidget()
{
	//连接界面
	m_ConnectSetup = new QPushButton(tr("S"));
	m_ConnectSetup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_ConnectMachine = new QPushButton(tr("OFF"));
	m_ConnectMachine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_WaterFlow = new QLabel(tr("FLOW"));
	m_GasPa = new QLabel(tr("PA"));
	QVBoxLayout *setLayout = new QVBoxLayout;
	QSpacerItem *verticalSpacer;
	verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	setLayout->addItem(verticalSpacer);
	setLayout->addWidget(m_ConnectSetup);
	setLayout->setStretch(0, 2);
	setLayout->setStretch(1, 1);


	QHBoxLayout *TopLeftLayout = new QHBoxLayout;
	TopLeftLayout->addWidget(m_ConnectMachine);
	TopLeftLayout->addLayout(setLayout);
	TopLeftLayout->setStretch(0, 2);
	TopLeftLayout->setStretch(1, 1);

	m_QMachineWidget = new QMachineWidget(this);
	m_QMachineWidget->show();
	m_QMachineWidget->move(100,100);
	QVBoxLayout *LeftLayout = new QVBoxLayout;
	LeftLayout->addWidget(m_QMachineWidget);


	QGridLayout *MainLayout = new QGridLayout;
	MainLayout->addLayout(TopLeftLayout,0,0);
	MainLayout->addLayout(LeftLayout,1,0);
	MainLayout->setColumnStretch(0, 1);
	MainLayout->setColumnStretch(1, 1);
	MainLayout->setRowStretch(0, 1);
	MainLayout->setRowStretch(1, 10);
	//QVBoxLayout *LeftLayout = new QVBoxLayout;
	//QHBoxLayout *TopRightLayout = new QHBoxLayout;
	//QVBoxLayout *RightLayout = new QVBoxLayout;



	ui.centralWidget->setLayout(MainLayout);
}