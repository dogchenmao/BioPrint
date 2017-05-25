#pragma once

#include <QWidget>
#include "QSelfPushButton.h"
#include "QSelfToolButton.h"
class QLabel;

class QTitleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit QTitleWidget(QWidget *parent = 0);
	void translateLanguage();

signals:
	void showMin();
	void showMax();
	void showMainMenu();
	void closeWidget();

	public slots:
	void turnPage(QString current_page);

protected:
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);

private:
	QPoint press_point;//��갴��ȥ�ĵ�
	bool is_move;

	QLabel *version_title; //����
	QSelfPushButton *main_menu_button; //���˵�
	QSelfPushButton *min_button; //��С��
	QSelfPushButton *max_button; //���
	QSelfPushButton *close_button; //�ر�

	QList<QSelfToolButton *> button_list;
};
