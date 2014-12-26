#include "percthread.h"
#include "perctype.h"
#include "quickfind.h"
#include "quickunion.h"
#include "quickunioncompressed.h"
#include "weightedquickunion.h"
#include "stopwatch.h"

#include <QDebug>

// It is recommended to use C++11's random number generation facilities to replace rand(). (since C++11)
// #include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

PercThread::PercThread(UFType uf_type, int sim_size, bool silent) : m_stop(false)
{
    IUnionFind *uf;

    switch (uf_type) {
        case ufTypeQuickFind:
            uf = new QuickFind(sim_size*sim_size + 2);
            m_name = "QuickFind";
            break;
        case ufTypeQuickUnion:
            uf = new QuickUnion(sim_size*sim_size + 2);
            m_name = "QuickUnion";
            break;
        case ufTypeCQuickUnion:
            uf = new QuickUnionCompressed(sim_size*sim_size + 2);
            m_name = "Compressed QuickUnion";
            break;
        case ufTypeWQuickUnion:
            uf = new WeightedQuickUnion(sim_size*sim_size + 2);
            m_name = "WeightedQuickUnion";
             break;
        case ufTypeWCQuickUnion:
            uf = new WeightedQuickUnionCompressed(sim_size*sim_size + 2);
            m_name = "Compressed WeightedQuickUnion";
            break;
        default:
            qDebug() << "PercThread: Undefined percolation type\n";
    }
    m_size = sim_size;
    m_silent = silent;
    m_percolation = new Percolation(sim_size, uf);
}

PercThread::~PercThread()
{
    delete m_percolation;    
}

void PercThread::setPercWidget(PercWidget *percwidget)
{
    m_percwidget = percwidget;
}



void PercThread::stop()
{
    qDebug()<<"Thread::stop called: "<<currentThreadId();
    QMutexLocker locker(&m_mutex);
    m_stop = true;
}
void PercThread::pause()
{

}

void PercThread::updatePercolation()
{
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++) {
            if (m_percolation->isOpen(i,j) == true) {
                m_percwidget->percPicture()->pixel(i,j) = Qt::white;
            }
            if (m_percolation->isFull(i,j) == true) {
                m_percwidget->percPicture()->pixel(i,j) = Qt::blue;
            }
        }
    m_percwidget->update();
}

void PercThread::run() {
    qDebug()<<"From worker thread: "<<currentThreadId();
    m_stop = false;

    srand(time(0));

    int opened_sites = 0;
    m_percolation->reset();
    m_percwidget->percPicture()->reset();
    m_percwidget->update();

    StopWatch sw;

    sw.start();
    while (1) {
        // performs T=sim_size independent computational experiments on an N= sim_count N-by-N grid
        // Initialize all sites to be blocked.
        // m_percolation->reset();

        // Repeat the following until the system percolates:
        //      Choose a site (row i, column j) uniformly at random among all blocked sites.
        int i = rand() % m_size;
        int j = rand() % m_size;

        if ( m_percolation->isOpen(i,j) == false) {
            m_percolation->open(i,j);
            opened_sites ++;
            if ((opened_sites % 100) == 0) {
                emit percolationSiteOpened(opened_sites, double(opened_sites) / double(m_size*m_size));
            }
        } else
            continue;

        // Update percolation picture
        if (m_silent == false)
            updatePercolation();

        if (m_percolation->percolates()) {
            double secs = sw.stop();
            double threshhold = double(opened_sites) / double(m_size*m_size);
            emit percolationSiteOpened(opened_sites, threshhold);
            emit percolates(secs);
            updatePercolation();
            break;
        }

        QMutexLocker locker(&m_mutex);
        if (m_stop) break;
    }



}
