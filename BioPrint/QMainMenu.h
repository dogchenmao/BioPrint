#pragma once

#include <QMenu>

class QMainMenu : public QMenu
{
	Q_OBJECT

public:
	explicit QMainMenu(QWidget *parent = 0);

	void translateActions();

signals:
	void showSettingDialog();
	void showNewCharacter();
	void showAboutUs();

private:
	void createActions();

private:
	QAction *action_setting;        //设置
	QAction *action_help_online;    //在线帮助
	QAction *action_login_home;     //Regenovo网站
	QAction *action_about_us;       //关于我们
};