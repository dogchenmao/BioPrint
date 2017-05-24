/********************************************************************************
** Form generated from reading UI file 'QMachineWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMACHINEWIDGET_H
#define UI_QMACHINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMachineWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_4;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBox;
    QLabel *label_5;
    QSpinBox *spinBox_2;
    QGridLayout *gridLayout;
    QPushButton *pushButtonXAdd;
    QPushButton *pushButtonYSub;
    QPushButton *pushButtonYAdd;
    QPushButton *pushButtonZAdd;
    QPushButton *pushButtonMoveXSub;
    QPushButton *pushButtonZSub;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QSlider *horizontalSlider;
    QLCDNumber *lcdNumber;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *QMachineWidget)
    {
        if (QMachineWidget->objectName().isEmpty())
            QMachineWidget->setObjectName(QStringLiteral("QMachineWidget"));
        QMachineWidget->resize(347, 556);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QMachineWidget->sizePolicy().hasHeightForWidth());
        QMachineWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(QMachineWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(QMachineWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radioButton = new QRadioButton(groupBox);
        buttonGroup = new QButtonGroup(QMachineWidget);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy1);
        radioButton->setChecked(true);

        horizontalLayout->addWidget(radioButton);

        radioButton_4 = new QRadioButton(groupBox);
        buttonGroup->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        sizePolicy1.setHeightForWidth(radioButton_4->sizePolicy().hasHeightForWidth());
        radioButton_4->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(radioButton_4);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(2000);
        spinBox->setSingleStep(100);
        spinBox->setValue(1200);

        horizontalLayout_3->addWidget(spinBox);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(2000);
        spinBox_2->setSingleStep(100);
        spinBox_2->setValue(1000);

        horizontalLayout_3->addWidget(spinBox_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(9);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        pushButtonXAdd = new QPushButton(groupBox);
        pushButtonXAdd->setObjectName(QStringLiteral("pushButtonXAdd"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonXAdd->sizePolicy().hasHeightForWidth());
        pushButtonXAdd->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButtonXAdd, 0, 0, 1, 1);

        pushButtonYSub = new QPushButton(groupBox);
        pushButtonYSub->setObjectName(QStringLiteral("pushButtonYSub"));
        sizePolicy2.setHeightForWidth(pushButtonYSub->sizePolicy().hasHeightForWidth());
        pushButtonYSub->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButtonYSub, 1, 1, 1, 1);

        pushButtonYAdd = new QPushButton(groupBox);
        pushButtonYAdd->setObjectName(QStringLiteral("pushButtonYAdd"));
        sizePolicy2.setHeightForWidth(pushButtonYAdd->sizePolicy().hasHeightForWidth());
        pushButtonYAdd->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButtonYAdd, 0, 1, 1, 1);

        pushButtonZAdd = new QPushButton(groupBox);
        pushButtonZAdd->setObjectName(QStringLiteral("pushButtonZAdd"));
        sizePolicy1.setHeightForWidth(pushButtonZAdd->sizePolicy().hasHeightForWidth());
        pushButtonZAdd->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButtonZAdd, 0, 2, 1, 1);

        pushButtonMoveXSub = new QPushButton(groupBox);
        pushButtonMoveXSub->setObjectName(QStringLiteral("pushButtonMoveXSub"));
        sizePolicy2.setHeightForWidth(pushButtonMoveXSub->sizePolicy().hasHeightForWidth());
        pushButtonMoveXSub->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButtonMoveXSub, 1, 0, 1, 1);

        pushButtonZSub = new QPushButton(groupBox);
        pushButtonZSub->setObjectName(QStringLiteral("pushButtonZSub"));
        sizePolicy1.setHeightForWidth(pushButtonZSub->sizePolicy().hasHeightForWidth());
        pushButtonZSub->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButtonZSub, 1, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 2);

        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(QMachineWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider);

        lcdNumber = new QLCDNumber(groupBox_3);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setLineWidth(0);
        lcdNumber->setSmallDecimalPoint(false);

        horizontalLayout_5->addWidget(lcdNumber);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(QMachineWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        sizePolicy3.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        sizePolicy3.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(pushButton_9);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalLayout_3->setStretch(0, 3);

        verticalLayout->addWidget(groupBox_2);

        verticalLayout->setStretch(0, 10);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 4);

        retranslateUi(QMachineWidget);

        QMetaObject::connectSlotsByName(QMachineWidget);
    } // setupUi

    void retranslateUi(QWidget *QMachineWidget)
    {
        QMachineWidget->setWindowTitle(QApplication::translate("QMachineWidget", "QMachineWidget", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("QMachineWidget", "\350\275\264\347\247\273\345\212\250", Q_NULLPTR));
        label->setText(QApplication::translate("QMachineWidget", "\347\247\273\345\212\250\346\226\271\345\274\217:", Q_NULLPTR));
        radioButton->setText(QApplication::translate("QMachineWidget", "\350\277\236\347\273\255", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("QMachineWidget", "\345\233\272\345\256\232", Q_NULLPTR));
        lineEdit->setInputMask(QApplication::translate("QMachineWidget", "1", Q_NULLPTR));
        label_2->setText(QApplication::translate("QMachineWidget", "mm", Q_NULLPTR));
        label_3->setText(QApplication::translate("QMachineWidget", "\351\200\237\345\272\246(mm/min):  X/Y\350\275\264", Q_NULLPTR));
        label_5->setText(QApplication::translate("QMachineWidget", "Z\350\275\264", Q_NULLPTR));
        pushButtonXAdd->setText(QApplication::translate("QMachineWidget", "X+", Q_NULLPTR));
        pushButtonYSub->setText(QApplication::translate("QMachineWidget", "Y-", Q_NULLPTR));
        pushButtonYAdd->setText(QApplication::translate("QMachineWidget", "Y+", Q_NULLPTR));
        pushButtonZAdd->setText(QApplication::translate("QMachineWidget", "Z+", Q_NULLPTR));
        pushButtonMoveXSub->setText(QApplication::translate("QMachineWidget", "X-", Q_NULLPTR));
        pushButtonZSub->setText(QApplication::translate("QMachineWidget", "Z-", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("QMachineWidget", "\345\216\213\345\212\233\345\200\274", Q_NULLPTR));
        label_4->setText(QApplication::translate("QMachineWidget", "mmPa", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("QMachineWidget", "\345\205\266\344\273\226\345\212\250\344\275\234", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("QMachineWidget", "\350\207\252\345\212\250\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("QMachineWidget", "\345\212\240\350\275\275\345\226\267\345\244\264", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("QMachineWidget", "\345\210\207\346\215\242\345\226\267\345\244\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QMachineWidget: public Ui_QMachineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMACHINEWIDGET_H
