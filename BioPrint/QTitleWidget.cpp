#include "QTitleWidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QSignalMapper>

QTitleWidget::QTitleWidget(QWidget *parent)
: QWidget(parent)
{


	version_title = new QLabel();
	main_menu_button = new QSelfPushButton();
	min_button = new QSelfPushButton();
	max_button = new QSelfPushButton();
	close_button = new QSelfPushButton();

	version_title->setStyleSheet("color:black;");

	//ÉèÖÃÍ¼Æ¬
	main_menu_button->loadPixmap(":/BioPrint/res/sysButton/main_menu");
	min_button->loadPixmap(":/BioPrint/res/sysButton/min_button");
	max_button->loadPixmap(":/BioPrint/res/sysButton/max_button");
	close_button->loadPixmap(":/BioPrint/res/sysButton/close_button");

	connect(main_menu_button, SIGNAL(clicked()), this, SIGNAL(showMainMenu()));
	connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
	connect(max_button, SIGNAL(clicked()), this, SIGNAL(showMax()));
	connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));

	QHBoxLayout *title_layout = new QHBoxLayout();
	title_layout->addWidget(version_title, 0, Qt::AlignVCenter);
	title_layout->addStretch();
	title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
	title_layout->addWidget(min_button, 0, Qt::AlignTop);
	title_layout->addWidget(max_button, 0, Qt::AlignTop);
	title_layout->addWidget(close_button, 0, Qt::AlignTop);
	title_layout->setSpacing(0);
	title_layout->setContentsMargins(0, 0, 5, 0);

	version_title->setContentsMargins(15, 0, 0, 0);


	this->translateLanguage();

	this->setLayout(title_layout);
	is_move = false;
}

void QTitleWidget::translateLanguage()
{
	version_title->setText(tr("DEMO"));
	main_menu_button->setToolTip(tr("main menu"));
	min_button->setToolTip(tr("minimize"));
	max_button->setToolTip(tr("maximize"));
	close_button->setToolTip(tr("close"));

}

void QTitleWidget::mousePressEvent(QMouseEvent *e)
{
	press_point = e->pos();
	is_move = true;
}

void QTitleWidget::mouseMoveEvent(QMouseEvent *e)
{
	if ((e->buttons() == Qt::LeftButton) && is_move)
	{
		static QWidget* parent_widget = this->topLevelWidget();
		QPoint parent_point = parent_widget->pos();
		parent_point.setX(parent_point.x() + e->x() - press_point.x());
		parent_point.setY(parent_point.y() + e->y() - press_point.y());
		parent_widget->move(parent_point);
	}
}

void QTitleWidget::mouseReleaseEvent(QMouseEvent *)
{
	if (is_move)
	{
		is_move = false;
	}
}

void QTitleWidget::mouseDoubleClickEvent(QMouseEvent *)
{
	emit showMax();
}

void QTitleWidget::turnPage(QString current_page)
{
	bool ok;
	int current_index = current_page.toInt(&ok, 10);

	for (int i = 0; i<button_list.count(); i++)
	{
		QSelfToolButton *tool_button = button_list.at(i);
		if (current_index == i)
		{
			tool_button->setMousePress(true);
		}
		else
		{
			tool_button->setMousePress(false);
		}
	}
}
