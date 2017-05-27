#include "BioPrint.h"
#include <QtWidgets/QOpenGLWidget>
#include <QApplication>
#include <QDesktopWidget>

BioPrint::BioPrint(QWidget *parent)
: QMainWindow(parent), flag(false)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	InitWidget();
	ConnectSignalSlot();

	location = this->geometry();
	startTimer(1000);
}
BioPrint::~BioPrint()
{
	
}

void BioPrint::InitWidget()
{
	//串口类
	m_QMySerialPort = new QMySerialPort(this);

	//喷头类
	m_QNozzleInfo = new QNozzleInfo(this);

	//运动控制类
	m_MotionControl = new MotionControl(this);

	//窗口类-喷头
	m_QMachinePTWidget = new QMachinePTWidget(this);
	ui.LeftLayout_D_U->addWidget(m_QMachinePTWidget);
	m_QMachinePTWidget->show();

	//窗口类-设备控制
	m_QMachineWidget = new QMachineWidget;
	ui.LeftLayout_U->addWidget(m_QMachineWidget);
	m_QMachineWidget->show();

	//窗口类-模型显示
	m_QModelView = new QModelView;
	ui.RightLayout_L_U->addWidget(m_QModelView);
	m_QModelView->show();

	//窗口类-标题栏
	m_QTitleWidget = new QTitleWidget();
	ui.TitleLayout->addWidget(m_QTitleWidget);
	m_QModelView->show();
	
	////窗口类-主菜单
	m_QMainMenu = new QMainMenu();
	m_QSystemTray = new QSystemTray(this);
	QString	test = "G01 X100 Y100 Z100 F10";
	m_MotionControl->SendPackage(test);
}

void BioPrint::ConnectSignalSlot()
{
	QObject::connect(m_QMySerialPort, SIGNAL(signalUpdataNozzleInfo(QByteArray)), m_QNozzleInfo, SLOT(slotUpdataNozzleInfo(QByteArray)));
	QObject::connect(m_QMySerialPort, SIGNAL(signalUpdataNozzleTemp(QByteArray)), m_QNozzleInfo, SLOT(slotUpdataNozzleTemp(QByteArray)));

	QObject::connect(m_QNozzleInfo, SIGNAL(signalNozzleStoreToWidget(QMap <NozzleStoreRoom, OneNozzleStore>)), m_QMachinePTWidget, SLOT(updataNozzle(QMap <NozzleStoreRoom, OneNozzleStore>)));
	
	QObject::connect(m_QTitleWidget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
	QObject::connect(m_QTitleWidget, SIGNAL(showMin()), this, SLOT(showMinimized()));
	QObject::connect(m_QTitleWidget, SIGNAL(showMax()), this, SLOT(showMax()));
	QObject::connect(m_QTitleWidget, SIGNAL(closeWidget()), this, SLOT(hide()));

	QObject::connect(this, SIGNAL(repaint()), this, SLOT(hide()));

	connect(m_QSystemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));

	m_QSystemTray->show();
}

void BioPrint::setModelWidget()
{

}
void BioPrint::setProjectWidget()
{

}
void BioPrint::showMax()
{
	static bool is_max = false;
	if (is_max)
	{
		this->setGeometry(location);
	}
	else
	{
		//获取当前界面的位置
		location = this->geometry();
		this->setGeometry(QApplication::desktop()->availableGeometry());
	}
	is_max = !is_max;
	update();
}

void BioPrint::showMainMenu()
{
	//设置主菜单出现的位置
	QPoint p = rect().topRight();
	p.setX(p.x() - 150);
	p.setY(p.y() + 22);
	m_QMainMenu->exec(this->mapToGlobal(p));
}
void BioPrint::paintEvent(QPaintEvent *)
{
	int height = this->height();
	int width = this->width();
	QPointF points[5] = { QPointF(0, 0), QPointF(0, height - 1), QPointF(width - 1, height - 1), QPointF(width - 1, 0), QPointF(0, 0) };

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QLinearGradient linearGradient(0, 0, 1, height);
	//linearGradient.setColorAt(0.1, QColor(255, 232, 224));
	//linearGradient.setColorAt(0.2, QColor(255, 213, 198));
	//linearGradient.setColorAt(0.3, QColor(255, 189, 164));
	linearGradient.setColorAt(0.2, QColor(255, 69, 0));
	linearGradient.setColorAt(0.4, QColor(255, 93, 33));
	linearGradient.setColorAt(0.6, QColor(255, 108, 53));
	linearGradient.setColorAt(0.8, QColor(255, 134, 89));
	linearGradient.setColorAt(1.0, QColor(255, 167, 134));

	painter.setPen(QPen(QBrush(linearGradient), 1));
	painter.drawPolyline(points, 5);


}
void BioPrint::timerEvent(QTimerEvent *)
{

}