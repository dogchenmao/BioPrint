#pragma once

#include <QToolButton>

class QSelfToolButton : public QToolButton
{
	Q_OBJECT

public:
	explicit QSelfToolButton(QString pic_name, QWidget *parent = 0);
	~QSelfToolButton();
	void setMousePress(bool mouse_press);

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);

public:
	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
};

