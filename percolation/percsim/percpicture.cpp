#include "percpicture.h"

PercPicture::PercPicture(int hSize, int vSize, QColor fillcolor)
{
    m_hSize = hSize;
    m_vSize = vSize;
    m_fillcolor = fillcolor;

    m_pict = new QColor*[m_hSize];
    for (int i = 0; i < m_hSize; i++)
        m_pict[i] = new QColor[m_vSize];
    reset();
}

PercPicture::~PercPicture()
{
    for (int i = 0; i < m_hSize; i++)
        delete [] m_pict[i];
    delete [] m_pict;
}

void PercPicture::reset()
{
    for (int i = 0; i < m_hSize; i++)
        for (int j = 0; j < m_vSize; j++)
                m_pict[i][j] = m_fillcolor;
}

QColor & PercPicture::pixel(int x, int y)
{
    return m_pict[x][y]; // try to change this value by its reference
}

int PercPicture::getHSize()
{
    return m_hSize;
}

int PercPicture::getVSize()
{
    return m_vSize;
}
