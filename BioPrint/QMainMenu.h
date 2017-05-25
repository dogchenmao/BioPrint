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
	QAction *action_setting;        //����
	QAction *action_help_online;    //���߰���
	QAction *action_login_home;     //Regenovo��վ
	QAction *action_about_us;       //��������
};