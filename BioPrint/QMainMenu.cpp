#include "QMainMenu.h"

QMainMenu::QMainMenu(QWidget *widget)
: QMenu(widget)
{
	this->createActions();
	this->translateActions();
}

void QMainMenu::createActions()
{
	//创建菜单项
	action_setting = new QAction(this);
	action_help_online = new QAction(this);
	action_login_home = new QAction(this);
	action_about_us = new QAction(this);

	action_about_us->setIcon(QIcon(":/mainMenu/about"));
	action_help_online->setIcon(QIcon(":/mainMenu/help"));
	action_setting->setIcon(QIcon(":/mainMenu/setting"));

	//添加菜单项
	this->addAction(action_setting);
	this->addSeparator();
	this->addAction(action_help_online);
	this->addAction(action_login_home);
	this->addAction(action_about_us);

	//设置信号连接
	QObject::connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
	QObject::connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));
}

void QMainMenu::translateActions()
{
	action_setting->setText(tr("setting"));
	action_help_online->setText(tr("help online"));
	action_login_home->setText(tr("login home"));
	action_about_us->setText(tr("about us"));
}
