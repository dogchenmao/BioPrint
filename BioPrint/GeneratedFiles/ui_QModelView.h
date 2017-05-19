/********************************************************************************
** Form generated from reading UI file 'QModelView.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMODELVIEW_H
#define UI_QMODELVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QOpenGLWidget>

QT_BEGIN_NAMESPACE

class Ui_QModelView
{
public:

    void setupUi(QOpenGLWidget *QModelView)
    {
        if (QModelView->objectName().isEmpty())
            QModelView->setObjectName(QStringLiteral("QModelView"));
        QModelView->resize(1067, 632);

        retranslateUi(QModelView);

        QMetaObject::connectSlotsByName(QModelView);
    } // setupUi

    void retranslateUi(QOpenGLWidget *QModelView)
    {
        QModelView->setWindowTitle(QApplication::translate("QModelView", "QModelView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QModelView: public Ui_QModelView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMODELVIEW_H
