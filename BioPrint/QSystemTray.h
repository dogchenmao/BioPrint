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
	QMenu *tray_menu; //���̲˵�

	QAction *action_open;		 //�����
	QAction *action_connect;	//���ӶϿ�
	QAction *action_1;			//
	QAction *action_2;			 //
	QAction *action_close;		 //�ر�

};