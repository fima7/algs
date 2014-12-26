#include "percwidget.h"
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>
#include <QColor>


PercWidget::PercWidget(QWidget *parent, int hSize, int vSize, QColor color) :
    QWidget(parent)
{
    m_scale_factor = 1.0;
    m_scale = 1.0;
    m_percPicture = new PercPicture(hSize, vSize, color);
}

PercWidget::~PercWidget()
{
    qDebug() << "Delete PercWidget";

    delete m_percPicture;
}

void PercWidget::paintEvent (QPaintEvent *pe)
{
    QPainter qpainter (this);
    qpainter.scale(m_scale_factor, m_scale_factor);

    for (int i = 0; i < m_percPicture->getHSize(); i++)
        for (int j = 0; j < m_percPicture->getVSize(); j++) {
                qpainter.setPen( QPen( m_percPicture->pixel(i,j) ) );
                qpainter.drawPoint(i, j);
        }
}

PercPicture* PercWidget::percPicture()
{
    return m_percPicture;
}

double PercWidget::getScaleFactor()
{
    return m_scale_factor;
}


void PercWidget::wheelEvent (QWheelEvent *event)
{
    m_scale += event->delta()/120;
    if (m_scale > 0)
        m_scale_factor = m_scale;
    else if (m_scale < 0)
        m_scale_factor = -1/m_scale;
    else // == 0
        m_scale_factor = 1;

    qDebug() << sizeof(QColor);

    qDebug() << "Delta " << event->delta()/120;

    qDebug() << "PaintWidget::scale_factor " << m_scale_factor;
    QString s = QString::number(m_scale_factor);
    qDebug() << "PaintWidget::scale_factor str" << s;
    resize(m_scale_factor * size());

    update();
    event->ignore();
}





