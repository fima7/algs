#ifndef PERCPAINT_H
#define PERCPAINT_H

#include "percpicture.h"

#include <QWidget>

class PercWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PercWidget(QWidget *parent = 0, int hSize = 0, int vSize = 0, QColor fillcolor = Qt::black);
    virtual ~PercWidget();
    double getScaleFactor();
    PercPicture *percPicture();

public slots:
    void paintEvent (QPaintEvent *);
    void wheelEvent(QWheelEvent *);

private:
    qreal m_scale_factor;
    qreal m_scale;
    PercPicture *m_percPicture;
};

#endif // PERCPAINT_H
