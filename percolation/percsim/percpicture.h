#ifndef PERCPICTURE_H
#define PERCPICTURE_H

#include <QColor>

class PercPicture
{
public:
    PercPicture(int hSize = 0, int vSize = 0, QColor fillcolor = Qt::black);
    virtual ~PercPicture();
    QColor & pixel(int x, int y);
    int getHSize();
    int getVSize();
    void reset();
private:
    QColor m_fillcolor;
    QColor **m_pict;
    int m_hSize;
    int m_vSize;
};

#endif // PERCPICTURE_H
