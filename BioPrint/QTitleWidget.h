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
	QPoint press_point;//鼠标按下去的点
	bool is_move;

	QLabel *version_title; //标题
	QSelfPushButton *main_menu_button; //主菜单
	QSelfPushButton *min_button; //最小化
	QSelfPushButton *max_button; //最大化
	QSelfPushButton *close_button; //关闭

	QList<QSelfToolButton *> button_list;
};
