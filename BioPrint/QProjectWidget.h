#pragma once

#include <QWidget>
#include "ui_QProjectWidget.h"

class QProjectWidget : public QWidget
{
	Q_OBJECT

public:
	QProjectWidget(QWidget *parent = Q_NULLPTR);
	~QProjectWidget();

private:
	Ui::QProjectWidget ui;
};
