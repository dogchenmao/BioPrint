#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QSystemTrayIcon>

#include "QSystemTray.h"

QSystemTray::QSystemTray(QWidget *parent)
: QSystemTrayIcon(parent)
{
	this->createAction();
	this->translateLanguage();
}

QSystemTray::~QSystemTray()
{

}

void QSystemTray::translateLanguage()
{
	//��������ͼ����ʱ����ʾ
	this->setToolTip(tr("BioPrinter"));

	action_open->setText(QString::fromLocal8Bit("�����"));
	action_connect->setText(QString::fromLocal8Bit("����/�Ͽ�"));
	action_1->setText(QString::fromLocal8Bit("����A"));
	action_2->setText(QString::fromLocal8Bit("����B"));
	action_close->setText(QString::fromLocal8Bit("�ر�"));
}

void QSystemTray::createAction()
{
	this->setIcon(QIcon(":/BioPrint/res/logo.ico"));

	tray_menu = new QMenu();
	action_open = new QAction(this);
	action_connect = new QAction(this);
	action_1 = new QAction(this);
	action_2 = new QAction(this);
	action_close = new QAction(this);

	//��Ӳ˵���
	tray_menu->addAction(action_open);
	tray_menu->addSeparator();
	tray_menu->addAction(action_connect);
	tray_menu->addAction(action_1);
	tray_menu->addAction(action_2);
	tray_menu->addSeparator();
	tray_menu->addAction(action_close);

	//�����ź�����
	QObject::connect(action_open, SIGNAL(triggered(bool)), this, SIGNAL(showWidget()));
	QObject::connect(action_connect, SIGNAL(triggered(bool)), this, SIGNAL(logoutWidget()));
	QObject::connect(action_1, SIGNAL(triggered(bool)), this, SIGNAL(setUp()));
	QObject::connect(action_2, SIGNAL(triggered(bool)), this, SIGNAL(aboutUs()));
	connect(action_close, SIGNAL(triggered()), qApp, SLOT(quit()));
	this->setContextMenu(tray_menu);
}