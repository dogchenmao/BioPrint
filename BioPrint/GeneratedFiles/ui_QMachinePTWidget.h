/********************************************************************************
** Form generated from reading UI file 'QMachinePTWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMACHINEPTWIDGET_H
#define UI_QMACHINEPTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMachinePTWidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *QMachinePTWidget)
    {
        if (QMachinePTWidget->objectName().isEmpty())
            QMachinePTWidget->setObjectName(QStringLiteral("QMachinePTWidget"));
        QMachinePTWidget->resize(1161, 696);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(QMachinePTWidget->sizePolicy().hasHeightForWidth());
        QMachinePTWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(QMachinePTWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(QMachinePTWidget);
        buttonGroup = new QButtonGroup(QMachinePTWidget);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pushButton_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_2, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 4, 1, 1);

        pushButton_3 = new QPushButton(QMachinePTWidget);
        buttonGroup->addButton(pushButton_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_3, 1, 5, 1, 1);

        pushButton = new QPushButton(QMachinePTWidget);
        buttonGroup->addButton(pushButton);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 6, 1, 1);

        pushButton_4 = new QPushButton(QMachinePTWidget);
        buttonGroup->addButton(pushButton_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_4, 1, 7, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 8, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 7);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 10);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 10);
        gridLayout->setColumnStretch(4, 1);
        gridLayout->setColumnStretch(5, 10);
        gridLayout->setColumnStretch(6, 1);
        gridLayout->setColumnStretch(7, 10);
        gridLayout->setColumnStretch(8, 1);

        retranslateUi(QMachinePTWidget);

        QMetaObject::connectSlotsByName(QMachinePTWidget);
    } // setupUi

    void retranslateUi(QWidget *QMachinePTWidget)
    {
        QMachinePTWidget->setWindowTitle(QApplication::translate("QMachinePTWidget", "QMachinePTWidget", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QMachinePTWidget", "...", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("QMachinePTWidget", "...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QMachinePTWidget", "...", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("QMachinePTWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QMachinePTWidget: public Ui_QMachinePTWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMACHINEPTWIDGET_H
