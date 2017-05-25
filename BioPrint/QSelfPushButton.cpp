#include "QSelfPushButton.h"

QSelfPushButton::QSelfPushButton(QWidget *parent)
:QPushButton(parent)
{
	status = NORMAL;
	mouse_press = false;
}

QSelfPushButton::~QSelfPushButton()
{

}

void QSelfPushButton::loadPixmap(QString pic_name)
{
	pixmap.load(pic_name);
	btn_width = pixmap.width() / 4;
	btn_height = pixmap.height();
	setFixedSize(btn_width, btn_height);
}

void QSelfPushButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void QSelfPushButton::mousePressEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
}

void QSelfPushButton::mouseReleaseEvent(QMouseEvent *)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if (mouse_press)
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void QSelfPushButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void QSelfPushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
}
