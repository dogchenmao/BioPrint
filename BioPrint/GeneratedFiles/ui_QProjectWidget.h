/********************************************************************************
** Form generated from reading UI file 'QProjectWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPROJECTWIDGET_H
#define UI_QPROJECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QProjectWidget
{
public:

    void setupUi(QWidget *QProjectWidget)
    {
        if (QProjectWidget->objectName().isEmpty())
            QProjectWidget->setObjectName(QStringLiteral("QProjectWidget"));
        QProjectWidget->resize(320, 640);

        retranslateUi(QProjectWidget);

        QMetaObject::connectSlotsByName(QProjectWidget);
    } // setupUi

    void retranslateUi(QWidget *QProjectWidget)
    {
        QProjectWidget->setWindowTitle(QApplication::translate("QProjectWidget", "QProjectWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QProjectWidget: public Ui_QProjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPROJECTWIDGET_H
