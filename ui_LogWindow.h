/********************************************************************************
** Form generated from reading UI file 'LogWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButtonDo;
    QComboBox *comboBoxServer;
    QPlainTextEdit *plainTextEditOutputModules;
    QTreeView *treeViewModules;
    QPlainTextEdit *plainTextEditOutputCall;
    QPlainTextEdit *plainTextEditOutputAll;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QPlainTextEdit *plainTextEditOutput;
    QWidget *tab_5;
    QPlainTextEdit *plainTextEditOutputSelected;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QTabWidget *tabWidget_3;
    QWidget *tab_11;
    QPlainTextEdit *plainTextEditLog;
    QWidget *tab_2;
    QPlainTextEdit *plainTextEditLogInstance;
    QWidget *tab_6;
    QPlainTextEdit *plainTextEditLogCall;
    QWidget *tab_12;
    QPlainTextEdit *plainTextEditLogCallVirt;
    QWidget *tab_7;
    QPlainTextEdit *plainTextEditLogString;
    QWidget *tab_8;
    QPlainTextEdit *plainTextEditLogPattern;
    QWidget *tab_9;
    QPlainTextEdit *plainTextEditLogCallInside;
    QWidget *tab_10;
    QPlainTextEdit *plainTextEditLogPointer;
    QWidget *tab_3;
    QPlainTextEdit *plainTextEditDumpImput;
    QPushButton *pushButtonDumpExecute;

    void setupUi(QWidget *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QStringLiteral("LogWindow"));
        LogWindow->resize(1680, 840);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(170, 170, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 191, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(212, 212, 159, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(85, 85, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(113, 113, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(212, 212, 191, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        LogWindow->setPalette(palette);
        LogWindow->setAutoFillBackground(false);
        tabWidget = new QTabWidget(LogWindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1661, 831));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButtonDo = new QPushButton(tab);
        pushButtonDo->setObjectName(QStringLiteral("pushButtonDo"));
        pushButtonDo->setGeometry(QRect(20, 0, 75, 20));
        comboBoxServer = new QComboBox(tab);
        comboBoxServer->setObjectName(QStringLiteral("comboBoxServer"));
        comboBoxServer->setGeometry(QRect(120, 0, 161, 22));
        plainTextEditOutputModules = new QPlainTextEdit(tab);
        plainTextEditOutputModules->setObjectName(QStringLiteral("plainTextEditOutputModules"));
        plainTextEditOutputModules->setGeometry(QRect(730, 380, 241, 421));
        plainTextEditOutputModules->setReadOnly(true);
        treeViewModules = new QTreeView(tab);
        treeViewModules->setObjectName(QStringLiteral("treeViewModules"));
        treeViewModules->setGeometry(QRect(980, 380, 201, 421));
        treeViewModules->header()->setVisible(false);
        plainTextEditOutputCall = new QPlainTextEdit(tab);
        plainTextEditOutputCall->setObjectName(QStringLiteral("plainTextEditOutputCall"));
        plainTextEditOutputCall->setGeometry(QRect(1190, 380, 241, 421));
        plainTextEditOutputCall->setReadOnly(true);
        plainTextEditOutputAll = new QPlainTextEdit(tab);
        plainTextEditOutputAll->setObjectName(QStringLiteral("plainTextEditOutputAll"));
        plainTextEditOutputAll->setGeometry(QRect(1440, 0, 221, 801));
        plainTextEditOutputAll->setReadOnly(true);
        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 380, 721, 411));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        plainTextEditOutput = new QPlainTextEdit(tab_4);
        plainTextEditOutput->setObjectName(QStringLiteral("plainTextEditOutput"));
        plainTextEditOutput->setGeometry(QRect(10, 10, 701, 421));
        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        plainTextEditOutputSelected = new QPlainTextEdit(tab_5);
        plainTextEditOutputSelected->setObjectName(QStringLiteral("plainTextEditOutputSelected"));
        plainTextEditOutputSelected->setGeometry(QRect(0, 0, 711, 381));
        tabWidget_2->addTab(tab_5, QString());
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 0, 80, 22));
        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(410, 0, 70, 17));
        tabWidget_3 = new QTabWidget(tab);
        tabWidget_3->setObjectName(QStringLiteral("tabWidget_3"));
        tabWidget_3->setGeometry(QRect(10, 30, 1401, 331));
        tab_11 = new QWidget();
        tab_11->setObjectName(QStringLiteral("tab_11"));
        plainTextEditLog = new QPlainTextEdit(tab_11);
        plainTextEditLog->setObjectName(QStringLiteral("plainTextEditLog"));
        plainTextEditLog->setGeometry(QRect(0, 0, 1461, 311));
        tabWidget_3->addTab(tab_11, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        plainTextEditLogInstance = new QPlainTextEdit(tab_2);
        plainTextEditLogInstance->setObjectName(QStringLiteral("plainTextEditLogInstance"));
        plainTextEditLogInstance->setGeometry(QRect(-70, 0, 1461, 311));
        tabWidget_3->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        plainTextEditLogCall = new QPlainTextEdit(tab_6);
        plainTextEditLogCall->setObjectName(QStringLiteral("plainTextEditLogCall"));
        plainTextEditLogCall->setGeometry(QRect(0, 0, 1401, 311));
        tabWidget_3->addTab(tab_6, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        plainTextEditLogCallVirt = new QPlainTextEdit(tab_12);
        plainTextEditLogCallVirt->setObjectName(QStringLiteral("plainTextEditLogCallVirt"));
        plainTextEditLogCallVirt->setGeometry(QRect(0, 0, 1401, 311));
        tabWidget_3->addTab(tab_12, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        plainTextEditLogString = new QPlainTextEdit(tab_7);
        plainTextEditLogString->setObjectName(QStringLiteral("plainTextEditLogString"));
        plainTextEditLogString->setGeometry(QRect(0, 0, 1391, 311));
        tabWidget_3->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        plainTextEditLogPattern = new QPlainTextEdit(tab_8);
        plainTextEditLogPattern->setObjectName(QStringLiteral("plainTextEditLogPattern"));
        plainTextEditLogPattern->setGeometry(QRect(0, 0, 1401, 311));
        tabWidget_3->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        plainTextEditLogCallInside = new QPlainTextEdit(tab_9);
        plainTextEditLogCallInside->setObjectName(QStringLiteral("plainTextEditLogCallInside"));
        plainTextEditLogCallInside->setGeometry(QRect(0, 0, 1401, 311));
        tabWidget_3->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QStringLiteral("tab_10"));
        plainTextEditLogPointer = new QPlainTextEdit(tab_10);
        plainTextEditLogPointer->setObjectName(QStringLiteral("plainTextEditLogPointer"));
        plainTextEditLogPointer->setGeometry(QRect(0, 0, 1401, 311));
        tabWidget_3->addTab(tab_10, QString());
        tabWidget->addTab(tab, QString());
        plainTextEditOutputModules->raise();
        pushButtonDo->raise();
        comboBoxServer->raise();
        treeViewModules->raise();
        plainTextEditOutputCall->raise();
        plainTextEditOutputAll->raise();
        tabWidget_2->raise();
        pushButton->raise();
        checkBox->raise();
        tabWidget_3->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        plainTextEditDumpImput = new QPlainTextEdit(tab_3);
        plainTextEditDumpImput->setObjectName(QStringLiteral("plainTextEditDumpImput"));
        plainTextEditDumpImput->setGeometry(QRect(0, 10, 1601, 701));
        pushButtonDumpExecute = new QPushButton(tab_3);
        pushButtonDumpExecute->setObjectName(QStringLiteral("pushButtonDumpExecute"));
        pushButtonDumpExecute->setGeometry(QRect(120, 730, 80, 22));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(LogWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);
        tabWidget_3->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QWidget *LogWindow)
    {
        LogWindow->setWindowTitle(QApplication::translate("LogWindow", "LogWindow", Q_NULLPTR));
        pushButtonDo->setText(QApplication::translate("LogWindow", "Do", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("LogWindow", "All", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("LogWindow", "DefaultList", Q_NULLPTR));
        pushButton->setText(QApplication::translate("LogWindow", "Refresh", Q_NULLPTR));
        checkBox->setText(QApplication::translate("LogWindow", "Remember", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_11), QApplication::translate("LogWindow", "MAIN LOG", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_2), QApplication::translate("LogWindow", "INSTANCE", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_6), QApplication::translate("LogWindow", "CALL", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_12), QApplication::translate("LogWindow", "CALL-VIRT", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_7), QApplication::translate("LogWindow", "STRING", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_8), QApplication::translate("LogWindow", "PATTERN", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_9), QApplication::translate("LogWindow", "CALL-INSIDE", Q_NULLPTR));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_10), QApplication::translate("LogWindow", "POINTER", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("LogWindow", "Scanner", Q_NULLPTR));
        pushButtonDumpExecute->setText(QApplication::translate("LogWindow", "Exacute", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("LogWindow", "Dump", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
