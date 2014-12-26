#ifndef PERCWINDOW_H
#define PERCWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QProgressBar>
#include <QLabel>
#include "percwidget.h"
#include "newdialog.h" // to have the NewDialog::UFType
#include "perctype.h"
#include "percthread.h"

class PercWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PercWindow(QWidget *parent = 0, UFType uf_type = ufTypeQuickFind,
                        int percwindow_number = 0, int sim_size = 0, bool silent = true);
    virtual ~PercWindow();
    PercWidget *percWidget();

    void start();
    void pause();
    void stop();

public slots:
    void wheelEvent(QWheelEvent *);
    void siteOpened(int, double);
    void percolates(double);

private:
    QScrollArea *m_scrollArea;
    PercWidget *m_percWidget;    
    PercThread *m_thread;
    QProgressBar *m_progressBar;
    QLabel *m_thresholdLabel;
    QLabel *m_timeLabel;
};



#endif // PERCWINDOW_H
