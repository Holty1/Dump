#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogWindow.h"

class LogWindow : public QWidget
{

	Q_OBJECT
	static	QStandardItemModel* model;
public slots:
	void  AppendLog(int window, int color, bool newLine, QString  msg);

public:
	template<typename ... Args>
	void AppendLogFormat(int window, int color, bool newLine, const std::string& format, Args ... args);

public slots:
	bool CheckTextFile(const char* fileName);
public slots:
	void FindOpcodeCalls(const char* filePath, map< DWORD, string> moduleFunctions);
public:
	LogWindow(QWidget *parent = Q_NULLPTR);
	~LogWindow();

	
public slots:
	void  AppendTreeViewModules();
public slots:
	void  AppendTextBoxModules();

private slots:
    void on_pushButton_clicked();

private slots:
    void on_pushButtonDumpExecute_clicked();

private slots:
    void on_treeViewModules_clicked(const QModelIndex &index);

private slots:
    void on_treeViewModules_activated( QModelIndex &index);

private slots:
    void on_comboBoxMakerMethod_currentIndexChanged(const QString &arg1);



private slots:
    void on_pushButtonMakerModuleRefresh_clicked(bool checked);

private slots:
    void on_pushButtonMakerMake_clicked(bool checked);

private slots:
    void on_pushButtonDo_clicked();

private:
	Ui::LogWindow ui;
};
