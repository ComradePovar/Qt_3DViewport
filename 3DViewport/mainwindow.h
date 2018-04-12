#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

namespace Ui {
	class MainWindowClass;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

	~MainWindow();
private slots:

private:
	Ui::MainWindowClass* ui;
};

#endif