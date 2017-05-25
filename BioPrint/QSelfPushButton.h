#pragma once
#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>

class QSelfPushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit QSelfPushButton(QWidget *parent = 0);
	~QSelfPushButton();
	void loadPixmap(QString pic_name);

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *);

private:

	//枚举按钮的几种状态
	enum ButtonStatus{ NORMAL, ENTER, PRESS, NOSTATUS };
	ButtonStatus status;
	QPixmap pixmap;

	int btn_width; //按钮宽度
	int btn_height; //按钮高度
	bool mouse_press; //按钮左键是否按下
};
