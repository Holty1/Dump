/********************************************************************************
** Form generated from reading UI file 'SnifferForm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNIFFERFORM_H
#define UI_SNIFFERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnifferForm
{
public:
    QTabWidget *tabWidgetPacket;
    QWidget *tabWidgetPacketSend;
    QPlainTextEdit *plainTextEditPacketSendOutput;
    QCheckBox *checkBoxPacketSendEnable;
    QPushButton *pushButtonPacketSendSendPacket;
    QLineEdit *lineEditPacketSendSendPacket;
    QCheckBox *checkBoxPacketSendIgnoreHeaders;
    QLineEdit *lineEditPacketSendIgnoreHeaders;
    QCheckBox *checkBoxPacketSendOnlyHeaders;
    QLineEdit *lineEditPacketSendOnlyHeaders;
    QCheckBox *checkBoxEditPacketSendSendPacketIsSequence;
    QWidget *tabWidgetPacketRecv;
    QPlainTextEdit *plainTextEditPacketRecvOutput;
    QCheckBox *checkBoxPacketRecvEnable;
    QCheckBox *checkBoxPacketRecvIgnoreHeaders;
    QLineEdit *lineEditPacketRecvOnlyHeaders;
    QCheckBox *checkBoxPacketRecvOnlyHeaders;
    QLineEdit *lineEditPacketRecvIgnoreHeaders;
    QWidget *PacketSendRecv;
    QPlainTextEdit *plainTextEditPacketSendRecvOutput;
    QCheckBox *checkBoxPacketSendRecvEnable;
    QCheckBox *checkBoxPacketSendRecvIgnoreHeaders;
    QLineEdit *lineEditPacketSendRecvOnlyHeaders;
    QCheckBox *checkBoxPacketSendRecvOnlyHeaders;
    QLineEdit *lineEditPacketSendRecvIgnoreHeaders;
    QPushButton *pushButton;

    void setupUi(QWidget *SnifferForm)
    {
        if (SnifferForm->objectName().isEmpty())
            SnifferForm->setObjectName(QStringLiteral("SnifferForm"));
        SnifferForm->resize(1262, 801);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(108, 101, 99, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(162, 152, 149, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(135, 126, 124, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(54, 50, 49, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(72, 67, 66, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        SnifferForm->setPalette(palette);
        tabWidgetPacket = new QTabWidget(SnifferForm);
        tabWidgetPacket->setObjectName(QStringLiteral("tabWidgetPacket"));
        tabWidgetPacket->setGeometry(QRect(10, 10, 1241, 771));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        QBrush brush8(QColor(170, 161, 165, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush8);
        QBrush brush9(QColor(255, 242, 248, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush9);
        QBrush brush10(QColor(212, 201, 206, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(85, 80, 82, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(113, 107, 110, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush13(QColor(212, 208, 210, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        tabWidgetPacket->setPalette(palette1);
        tabWidgetPacketSend = new QWidget();
        tabWidgetPacketSend->setObjectName(QStringLiteral("tabWidgetPacketSend"));
        plainTextEditPacketSendOutput = new QPlainTextEdit(tabWidgetPacketSend);
        plainTextEditPacketSendOutput->setObjectName(QStringLiteral("plainTextEditPacketSendOutput"));
        plainTextEditPacketSendOutput->setGeometry(QRect(10, 70, 1221, 641));
        checkBoxPacketSendEnable = new QCheckBox(tabWidgetPacketSend);
        checkBoxPacketSendEnable->setObjectName(QStringLiteral("checkBoxPacketSendEnable"));
        checkBoxPacketSendEnable->setGeometry(QRect(10, 10, 70, 17));
        pushButtonPacketSendSendPacket = new QPushButton(tabWidgetPacketSend);
        pushButtonPacketSendSendPacket->setObjectName(QStringLiteral("pushButtonPacketSendSendPacket"));
        pushButtonPacketSendSendPacket->setGeometry(QRect(10, 720, 75, 23));
        lineEditPacketSendSendPacket = new QLineEdit(tabWidgetPacketSend);
        lineEditPacketSendSendPacket->setObjectName(QStringLiteral("lineEditPacketSendSendPacket"));
        lineEditPacketSendSendPacket->setGeometry(QRect(100, 720, 1081, 20));
        checkBoxPacketSendIgnoreHeaders = new QCheckBox(tabWidgetPacketSend);
        checkBoxPacketSendIgnoreHeaders->setObjectName(QStringLiteral("checkBoxPacketSendIgnoreHeaders"));
        checkBoxPacketSendIgnoreHeaders->setGeometry(QRect(10, 40, 111, 17));
        lineEditPacketSendIgnoreHeaders = new QLineEdit(tabWidgetPacketSend);
        lineEditPacketSendIgnoreHeaders->setObjectName(QStringLiteral("lineEditPacketSendIgnoreHeaders"));
        lineEditPacketSendIgnoreHeaders->setGeometry(QRect(140, 40, 321, 20));
        checkBoxPacketSendOnlyHeaders = new QCheckBox(tabWidgetPacketSend);
        checkBoxPacketSendOnlyHeaders->setObjectName(QStringLiteral("checkBoxPacketSendOnlyHeaders"));
        checkBoxPacketSendOnlyHeaders->setGeometry(QRect(500, 40, 121, 17));
        lineEditPacketSendOnlyHeaders = new QLineEdit(tabWidgetPacketSend);
        lineEditPacketSendOnlyHeaders->setObjectName(QStringLiteral("lineEditPacketSendOnlyHeaders"));
        lineEditPacketSendOnlyHeaders->setGeometry(QRect(630, 40, 331, 20));
        checkBoxEditPacketSendSendPacketIsSequence = new QCheckBox(tabWidgetPacketSend);
        checkBoxEditPacketSendSendPacketIsSequence->setObjectName(QStringLiteral("checkBoxEditPacketSendSendPacketIsSequence"));
        checkBoxEditPacketSendSendPacketIsSequence->setGeometry(QRect(1190, 720, 70, 17));
        checkBoxEditPacketSendSendPacketIsSequence->setChecked(true);
        tabWidgetPacket->addTab(tabWidgetPacketSend, QString());
        tabWidgetPacketRecv = new QWidget();
        tabWidgetPacketRecv->setObjectName(QStringLiteral("tabWidgetPacketRecv"));
        plainTextEditPacketRecvOutput = new QPlainTextEdit(tabWidgetPacketRecv);
        plainTextEditPacketRecvOutput->setObjectName(QStringLiteral("plainTextEditPacketRecvOutput"));
        plainTextEditPacketRecvOutput->setGeometry(QRect(10, 60, 1221, 671));
        checkBoxPacketRecvEnable = new QCheckBox(tabWidgetPacketRecv);
        checkBoxPacketRecvEnable->setObjectName(QStringLiteral("checkBoxPacketRecvEnable"));
        checkBoxPacketRecvEnable->setGeometry(QRect(10, 10, 70, 17));
        checkBoxPacketRecvIgnoreHeaders = new QCheckBox(tabWidgetPacketRecv);
        checkBoxPacketRecvIgnoreHeaders->setObjectName(QStringLiteral("checkBoxPacketRecvIgnoreHeaders"));
        checkBoxPacketRecvIgnoreHeaders->setGeometry(QRect(10, 30, 111, 17));
        lineEditPacketRecvOnlyHeaders = new QLineEdit(tabWidgetPacketRecv);
        lineEditPacketRecvOnlyHeaders->setObjectName(QStringLiteral("lineEditPacketRecvOnlyHeaders"));
        lineEditPacketRecvOnlyHeaders->setGeometry(QRect(570, 30, 331, 20));
        checkBoxPacketRecvOnlyHeaders = new QCheckBox(tabWidgetPacketRecv);
        checkBoxPacketRecvOnlyHeaders->setObjectName(QStringLiteral("checkBoxPacketRecvOnlyHeaders"));
        checkBoxPacketRecvOnlyHeaders->setGeometry(QRect(460, 30, 111, 17));
        lineEditPacketRecvIgnoreHeaders = new QLineEdit(tabWidgetPacketRecv);
        lineEditPacketRecvIgnoreHeaders->setObjectName(QStringLiteral("lineEditPacketRecvIgnoreHeaders"));
        lineEditPacketRecvIgnoreHeaders->setGeometry(QRect(120, 30, 321, 20));
        tabWidgetPacket->addTab(tabWidgetPacketRecv, QString());
        PacketSendRecv = new QWidget();
        PacketSendRecv->setObjectName(QStringLiteral("PacketSendRecv"));
        plainTextEditPacketSendRecvOutput = new QPlainTextEdit(PacketSendRecv);
        plainTextEditPacketSendRecvOutput->setObjectName(QStringLiteral("plainTextEditPacketSendRecvOutput"));
        plainTextEditPacketSendRecvOutput->setGeometry(QRect(10, 60, 1221, 681));
        checkBoxPacketSendRecvEnable = new QCheckBox(PacketSendRecv);
        checkBoxPacketSendRecvEnable->setObjectName(QStringLiteral("checkBoxPacketSendRecvEnable"));
        checkBoxPacketSendRecvEnable->setGeometry(QRect(10, 10, 70, 17));
        checkBoxPacketSendRecvIgnoreHeaders = new QCheckBox(PacketSendRecv);
        checkBoxPacketSendRecvIgnoreHeaders->setObjectName(QStringLiteral("checkBoxPacketSendRecvIgnoreHeaders"));
        checkBoxPacketSendRecvIgnoreHeaders->setGeometry(QRect(10, 30, 111, 17));
        lineEditPacketSendRecvOnlyHeaders = new QLineEdit(PacketSendRecv);
        lineEditPacketSendRecvOnlyHeaders->setObjectName(QStringLiteral("lineEditPacketSendRecvOnlyHeaders"));
        lineEditPacketSendRecvOnlyHeaders->setGeometry(QRect(600, 30, 331, 20));
        checkBoxPacketSendRecvOnlyHeaders = new QCheckBox(PacketSendRecv);
        checkBoxPacketSendRecvOnlyHeaders->setObjectName(QStringLiteral("checkBoxPacketSendRecvOnlyHeaders"));
        checkBoxPacketSendRecvOnlyHeaders->setGeometry(QRect(500, 30, 101, 17));
        lineEditPacketSendRecvIgnoreHeaders = new QLineEdit(PacketSendRecv);
        lineEditPacketSendRecvIgnoreHeaders->setObjectName(QStringLiteral("lineEditPacketSendRecvIgnoreHeaders"));
        lineEditPacketSendRecvIgnoreHeaders->setGeometry(QRect(140, 30, 321, 20));
        tabWidgetPacket->addTab(PacketSendRecv, QString());
        pushButton = new QPushButton(SnifferForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 0, 75, 23));

        retranslateUi(SnifferForm);

        tabWidgetPacket->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SnifferForm);
    } // setupUi

    void retranslateUi(QWidget *SnifferForm)
    {
        SnifferForm->setWindowTitle(QApplication::translate("SnifferForm", "SnifferForm", Q_NULLPTR));
        checkBoxPacketSendEnable->setText(QApplication::translate("SnifferForm", "Enable", Q_NULLPTR));
        pushButtonPacketSendSendPacket->setText(QApplication::translate("SnifferForm", "Send Packet", Q_NULLPTR));
        checkBoxPacketSendIgnoreHeaders->setText(QApplication::translate("SnifferForm", "Ignore Headers", Q_NULLPTR));
        checkBoxPacketSendOnlyHeaders->setText(QApplication::translate("SnifferForm", "Only Headers", Q_NULLPTR));
        checkBoxEditPacketSendSendPacketIsSequence->setText(QApplication::translate("SnifferForm", "Seq", Q_NULLPTR));
        tabWidgetPacket->setTabText(tabWidgetPacket->indexOf(tabWidgetPacketSend), QApplication::translate("SnifferForm", "Send", Q_NULLPTR));
        checkBoxPacketRecvEnable->setText(QApplication::translate("SnifferForm", "Enable", Q_NULLPTR));
        checkBoxPacketRecvIgnoreHeaders->setText(QApplication::translate("SnifferForm", "Ignore Headers", Q_NULLPTR));
        checkBoxPacketRecvOnlyHeaders->setText(QApplication::translate("SnifferForm", "Only Headers", Q_NULLPTR));
        tabWidgetPacket->setTabText(tabWidgetPacket->indexOf(tabWidgetPacketRecv), QApplication::translate("SnifferForm", "Recv", Q_NULLPTR));
        checkBoxPacketSendRecvEnable->setText(QApplication::translate("SnifferForm", "Enable", Q_NULLPTR));
        checkBoxPacketSendRecvIgnoreHeaders->setText(QApplication::translate("SnifferForm", "Ignore Headers", Q_NULLPTR));
        checkBoxPacketSendRecvOnlyHeaders->setText(QApplication::translate("SnifferForm", "Only Headers", Q_NULLPTR));
        tabWidgetPacket->setTabText(tabWidgetPacket->indexOf(PacketSendRecv), QApplication::translate("SnifferForm", "Mix", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SnifferForm", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SnifferForm: public Ui_SnifferForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNIFFERFORM_H
