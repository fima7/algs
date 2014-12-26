#include "percwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "percwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
    for (int i = 0; i < ufTypeEnd; i++)
        m_percWindowsNumber[i] = 0;
}

MainWindow::~MainWindow()
{
    qDebug() << "Delete MainWindow";
    delete ui;
}

void MainWindow::on_newButton_clicked()
{
    qDebug() << "New";
    NewDialog newDialog;
    UFType uf_type;
    int sim_size;

    if (newDialog.exec() == QDialog::Accepted) {

        list<UFType> perclist = newDialog.getList();
        sim_size = newDialog.getSimSize();
        bool silent = newDialog.getSilent();

        list<UFType>::iterator i;
        for (i=perclist.begin(); i != perclist.end(); i++) {
            m_percWindowsNumber[*i]++;
            PercWindow* percwindow = new PercWindow(this, *i, m_percWindowsNumber[*i], sim_size, silent);
            percwindow->show();
        }
    }

}

void MainWindow::on_startButton_clicked()
{
    qDebug() << "Start";
    QList<PercWindow*> list = this->findChildren<PercWindow*>();
    foreach (PercWindow *w, list)
            w->start();
}

void MainWindow::on_pauseButton_clicked()
{
    qDebug() << "Pause";
}

void MainWindow::on_stopButton_clicked()
{
    qDebug() << "Stop";
}
