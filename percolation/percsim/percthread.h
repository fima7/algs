#ifndef PERCTHREAD_H
#define PERCTHREAD_H

#include "perctype.h"
#include "percolation.h"
#include "percwidget.h"

#include <QThread>
#include <QMutex>
#include <QDebug>

#include <string>


class PercThread : public QThread
{
        Q_OBJECT

public:
    PercThread(UFType uf_type, int sim_size, bool silent);
    virtual ~PercThread();
    void stop();
    void pause();
    void setPercWidget(PercWidget *percwidget);
    void run();

private:
    QString m_name;
    int m_size;
    QMutex m_mutex;
    bool m_stop;
    Percolation *m_percolation;
    PercWidget *m_percwidget;
    bool m_silent;
    void updatePercolation();

signals:
    void percolationSiteOpened(int, double);
    void percolates(double secs);

};




#endif // PERCTHREAD_H
