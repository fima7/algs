#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "newdialog.h"
#include "percwindow.h"
#include "perctype.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_newButton_clicked();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    int m_percWindowsNumber[ufTypeEnd];
};

#endif // MAINWINDOW_H
