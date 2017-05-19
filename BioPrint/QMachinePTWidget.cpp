#include "QMachinePTWidget.h"
#include <QResizeEvent>


QMachinePTWidget::QMachinePTWidget(QWidget *parent)
: QWidget(parent), mybool(false)
{
	ui.setupUi(this);

	//m_Image.load(":/BioPrint/res/PTZ.png");
	startTimer(3000);
	setAutoFillBackground(true);  
	//if (!m_Image.isNull())
	//{
	//	QPalette pal(palette());
	//	pal.setBrush(QPalette::Window,
	//		QBrush(m_Image.scaled(size(), Qt::IgnoreAspectRatio,
	//		Qt::SmoothTransformation)));
	//	setPalette(pal);
	//}

	

	ui.pushButton->setAutoFillBackground(true);

	ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");

	ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
	ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
	ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");

}

QMachinePTWidget::~QMachinePTWidget()
{
}

void QMachinePTWidget::m_SetType(uint NozzleIndex, NozzleType type)
{
	
}


void QMachinePTWidget::resizeEvent(QResizeEvent *event)
{

}

void QMachinePTWidget::timerEvent(QTimerEvent *event)
{
	if (mybool)
	{
		ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");

		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");

		mybool = false;
	}
	else
	{
		ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");

		ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
		ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
		ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
			"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
		mybool = true;
	}

}