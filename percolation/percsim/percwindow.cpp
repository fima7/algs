#include "percwindow.h"

#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>

PercWindow::PercWindow(QWidget *parent, UFType uf_type, int percwindow_number,
                       int perc_size, bool silent) : QWidget(parent)
{
    setWindowFlags(Qt::Window);

    setAttribute(Qt::WA_DeleteOnClose, true);

    setGeometry(100,100, perc_size+30, perc_size+60);

    m_percWidget = new PercWidget (this, perc_size, perc_size);
    /*
     * When you use a layout, you do not need to pass a parent when constructing the child widgets.
     * The layout will automatically reparent the widgets (using QWidget::setParent()) so that they
     * are children of the widget on which the layout is installed.
     */
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
    m_scrollArea->viewport()->setAutoFillBackground(true);
    m_scrollArea->setWidget(m_percWidget);
    //m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    QStatusBar *statusBar = new QStatusBar;
    m_progressBar = new QProgressBar(this);
    m_progressBar->setMaximum(perc_size*perc_size);
    statusBar->addPermanentWidget(m_progressBar, 200);

    m_thresholdLabel = new QLabel(this);
    m_thresholdLabel->setText("0.0000");
    m_thresholdLabel->setStyleSheet("QLabel { color : green; }");
    statusBar->addPermanentWidget(m_thresholdLabel, 0);

    m_timeLabel = new QLabel(this);
    m_timeLabel->setStyleSheet("QLabel { color : green; }");
    m_timeLabel->setText("0.0000s");
    statusBar->addPermanentWidget(m_timeLabel, 0);

    // statusBar->show();

    // Widgets layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_scrollArea);
    layout->addWidget(statusBar);

    setLayout(layout); // sets PercWindow as a parent of all widgets added to layout.

    QString title;

    switch (uf_type) {
        case ufTypeQuickFind:
            title = QString("QuickFind: %1").arg(percwindow_number);
            break;
        case ufTypeQuickUnion:
            title = QString("QuickUnion: %1").arg(percwindow_number);
            break;
        case ufTypeWQuickUnion:
            title = QString("WeightedQuickUnion: %1").arg(percwindow_number);
            break;
        case ufTypeCQuickUnion:
            title = QString("QuickUnion compressed: %1").arg(percwindow_number);
            break;
        case ufTypeWCQuickUnion:
            title = QString("WeightedQuickUnion compressed: %1").arg(percwindow_number);
            break;
    }

    setWindowTitle(title);

    // Tread create
    m_thread = new PercThread(uf_type, perc_size, silent);
    m_thread->setPercWidget(m_percWidget);

    connect(m_thread, SIGNAL(percolationSiteOpened(int, double)), this, SLOT(siteOpened(int, double)));
    connect(m_thread, SIGNAL(percolates(double)), this, SLOT(percolates(double)));

}
void PercWindow::percolates(double secs)
{
    m_timeLabel->setStyleSheet("QLabel { color : red; }");
    m_thresholdLabel->setStyleSheet("QLabel { color : red; }");

    QString s_time = QString::number(secs, 'f', 4);
    s_time+="s";
    m_timeLabel->setText(s_time);
    //m_thresholdLabel->setStyleSheet("QLabel { background-color : gray; color : red; }");
}

void PercWindow::siteOpened(int opened_sites, double threshold)
{
    // qDebug() << "Opened";
    m_progressBar->setValue(opened_sites);
    QString s_thr = QString::number(threshold, 'f', 4);
    m_thresholdLabel->setText(s_thr);
}

PercWindow::~PercWindow()
{
    qDebug() << "Delete PercWindow: " << windowTitle();
    m_thread->stop();
    m_thread->wait();
    delete m_thread;
    delete m_percWidget;
}

PercWidget* PercWindow::percWidget()
{
    return m_percWidget;
}

void PercWindow::wheelEvent (QWheelEvent *event)
{

    QScrollBar* hSb = m_scrollArea->horizontalScrollBar();
    QScrollBar* vSb = m_scrollArea->verticalScrollBar();

    double factor = m_percWidget->getScaleFactor();

    int h_maximum = int(factor * m_percWidget->geometry().width() + ((factor - 1) * hSb->pageStep()/2));
    int v_maximum = int(factor * m_percWidget->geometry().height() + ((factor - 1) * vSb->pageStep()/2));
    int h = int(factor * hSb->value() + ((factor - 1) * hSb->pageStep()/2));
    int v = int(factor * vSb->value() + ((factor - 1) * vSb->pageStep()/2));

    qDebug() << "maximum vertical " << v_maximum << "vertical " << v;
    qDebug() << "maximum horizontal " << h_maximum << "horizontal " << h;

    hSb->setValue(h);
    vSb->setValue(v);

    hSb->setMinimum(0);
    hSb->setMaximum(h_maximum);

    vSb->setMinimum(0);
    vSb->setMaximum(v_maximum);
}


void PercWindow::start()
{
    m_thread->start();
    m_percWidget->update();
}

void PercWindow::pause()
{
    m_thread->pause();
    m_percWidget->update();
}

void PercWindow::stop()
{
    m_thread->stop();
    m_percWidget->update();
}




