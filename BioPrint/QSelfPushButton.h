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

	//ö�ٰ�ť�ļ���״̬
	enum ButtonStatus{ NORMAL, ENTER, PRESS, NOSTATUS };
	ButtonStatus status;
	QPixmap pixmap;

	int btn_width; //��ť���
	int btn_height; //��ť�߶�
	bool mouse_press; //��ť����Ƿ���
};
