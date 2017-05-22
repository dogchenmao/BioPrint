#include "QMachinePTWidget.h"
#include <QResizeEvent>


QMachinePTWidget::QMachinePTWidget(QWidget *parent)
: QWidget(parent), mybool(false)
{
	ui.setupUi(this);

	setAutoFillBackground(true);  

	ui.pushButton->setAutoFillBackground(true);

	ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
}

QMachinePTWidget::~QMachinePTWidget()
{
}

void QMachinePTWidget::updataNozzle(QMap<NozzleStoreRoom,OneNozzleStore> store)
{
	ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
	ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
		"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");

	QMap <NozzleStoreRoom, OneNozzleStore>::iterator it;
	for (it = store.begin(); it != store.end(); ++it)
	{
		switch (it.key())
		{
		case NozzleStoreRoomA:
			if (it.value().TYPE == NozzleTypeCold)
			{
				ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
			}
			else if (it.value().TYPE == NozzleTypeHot)
			{
				ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
			}
			else
			{
				ui.pushButton->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
			}
			break;
		case NozzleStoreRoomB:
			if (it.value().TYPE == NozzleTypeCold)
			{
				ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
			}
			else if (it.value().TYPE == NozzleTypeHot)
			{
				ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
			}
			else
			{
				ui.pushButton_2->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
			}
			break;
		case NozzleStoreRoomC:
			if (it.value().TYPE == NozzleTypeCold)
			{
				ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
			}
			else if (it.value().TYPE == NozzleTypeHot)
			{
				ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
			}
			else
			{
				ui.pushButton_3->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
			}
			break;
		case NozzleStoreRoomD:
			if (it.value().TYPE == NozzleTypeCold)
			{
				ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/LOW1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/LOW1.png);}");
			}
			else if (it.value().TYPE == NozzleTypeHot)
			{
				ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/HIGH1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/HIGH1.png);}");
			}
			else
			{
				ui.pushButton_4->setStyleSheet("QPushButton{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:hover{border-image: url(:/BioPrint/res/PTZ_1.png);}"
					"QPushButton:pressed{border-image: url(:/BioPrint/res/PTZ_1.png);}");
			}
			break;
		default:
			break;
		}
	}
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