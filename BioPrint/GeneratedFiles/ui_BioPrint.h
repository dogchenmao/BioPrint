/********************************************************************************
** Form generated from reading UI file 'BioPrint.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIOPRINT_H
#define UI_BIOPRINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BioPrintClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *TopLayout;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *LeftLayout;
    QVBoxLayout *LeftLayout_U;
    QVBoxLayout *LeftLayout_D;
    QHBoxLayout *LeftLayout_D_U;
    QHBoxLayout *LeftLayout_D_D;
    QHBoxLayout *RightLayout;
    QVBoxLayout *RightLayout_L;
    QHBoxLayout *RightLayout_L_U;
    QVBoxLayout *RightLayout_L_D;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *RightLayout_R;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *BottomLayout;
    QHBoxLayout *TitleLayout;

    void setupUi(QMainWindow *BioPrintClass)
    {
        if (BioPrintClass->objectName().isEmpty())
            BioPrintClass->setObjectName(QStringLiteral("BioPrintClass"));
        BioPrintClass->resize(1297, 828);
        BioPrintClass->setStyleSheet(QStringLiteral(""));
        BioPrintClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
        BioPrintClass->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(BioPrintClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 0, 2, 2);
        TopLayout = new QHBoxLayout();
        TopLayout->setSpacing(6);
        TopLayout->setObjectName(QStringLiteral("TopLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        TopLayout->addItem(verticalSpacer_4);


        gridLayout->addLayout(TopLayout, 1, 0, 1, 3);

        LeftLayout = new QVBoxLayout();
        LeftLayout->setSpacing(6);
        LeftLayout->setObjectName(QStringLiteral("LeftLayout"));
        LeftLayout_U = new QVBoxLayout();
        LeftLayout_U->setSpacing(6);
        LeftLayout_U->setObjectName(QStringLiteral("LeftLayout_U"));

        LeftLayout->addLayout(LeftLayout_U);

        LeftLayout_D = new QVBoxLayout();
        LeftLayout_D->setSpacing(6);
        LeftLayout_D->setObjectName(QStringLiteral("LeftLayout_D"));
        LeftLayout_D->setSizeConstraint(QLayout::SetDefaultConstraint);
        LeftLayout_D_U = new QHBoxLayout();
        LeftLayout_D_U->setSpacing(0);
        LeftLayout_D_U->setObjectName(QStringLiteral("LeftLayout_D_U"));

        LeftLayout_D->addLayout(LeftLayout_D_U);

        LeftLayout_D_D = new QHBoxLayout();
        LeftLayout_D_D->setSpacing(6);
        LeftLayout_D_D->setObjectName(QStringLiteral("LeftLayout_D_D"));

        LeftLayout_D->addLayout(LeftLayout_D_D);

        LeftLayout_D->setStretch(0, 3);
        LeftLayout_D->setStretch(1, 2);

        LeftLayout->addLayout(LeftLayout_D);

        LeftLayout->setStretch(0, 3);
        LeftLayout->setStretch(1, 2);

        gridLayout->addLayout(LeftLayout, 2, 0, 1, 1);

        RightLayout = new QHBoxLayout();
        RightLayout->setSpacing(6);
        RightLayout->setObjectName(QStringLiteral("RightLayout"));
        RightLayout_L = new QVBoxLayout();
        RightLayout_L->setSpacing(6);
        RightLayout_L->setObjectName(QStringLiteral("RightLayout_L"));
        RightLayout_L_U = new QHBoxLayout();
        RightLayout_L_U->setSpacing(6);
        RightLayout_L_U->setObjectName(QStringLiteral("RightLayout_L_U"));

        RightLayout_L->addLayout(RightLayout_L_U);

        RightLayout_L_D = new QVBoxLayout();
        RightLayout_L_D->setSpacing(6);
        RightLayout_L_D->setObjectName(QStringLiteral("RightLayout_L_D"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        RightLayout_L_D->addItem(verticalSpacer);


        RightLayout_L->addLayout(RightLayout_L_D);

        RightLayout_L->setStretch(0, 2);
        RightLayout_L->setStretch(1, 1);

        RightLayout->addLayout(RightLayout_L);

        RightLayout_R = new QVBoxLayout();
        RightLayout_R->setSpacing(6);
        RightLayout_R->setObjectName(QStringLiteral("RightLayout_R"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        RightLayout_R->addItem(verticalSpacer_3);


        RightLayout->addLayout(RightLayout_R);

        RightLayout->setStretch(0, 2);
        RightLayout->setStretch(1, 1);

        gridLayout->addLayout(RightLayout, 2, 1, 1, 2);

        BottomLayout = new QHBoxLayout();
        BottomLayout->setSpacing(6);
        BottomLayout->setObjectName(QStringLiteral("BottomLayout"));

        gridLayout->addLayout(BottomLayout, 3, 0, 1, 3);

        TitleLayout = new QHBoxLayout();
        TitleLayout->setSpacing(6);
        TitleLayout->setObjectName(QStringLiteral("TitleLayout"));

        gridLayout->addLayout(TitleLayout, 0, 0, 1, 3);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 3);
        gridLayout->setRowStretch(2, 25);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        BioPrintClass->setCentralWidget(centralWidget);

        retranslateUi(BioPrintClass);

        QMetaObject::connectSlotsByName(BioPrintClass);
    } // setupUi

    void retranslateUi(QMainWindow *BioPrintClass)
    {
        BioPrintClass->setWindowTitle(QApplication::translate("BioPrintClass", "BioPrint", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BioPrintClass: public Ui_BioPrintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIOPRINT_H
