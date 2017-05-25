#pragma once
#include <QSystemTrayIcon>

class QMenu;
class QAction;

class QSystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	explicit QSystemTray(QWidget *parent = 0);
	~QSystemTray();
	void translateLanguage();

private:
	void createAction();

private:
	QMenu *tray_menu; //托盘菜单

	QAction *action_open;		 //打开软件
	QAction *action_connect;	//连接断开
	QAction *action_1;			//
	QAction *action_2;			 //
	QAction *action_close;		 //关闭

};