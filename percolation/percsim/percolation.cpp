#include "percolation.h"
#include <QDebug>

// create N-by-N grid, with all sites blocked
Percolation::Percolation(int N, IUnionFind *uf)
{
    m_uf = uf;
    m_size = N;
    m_grid = new char *[m_size];
    this->reset();
}

// Delete N-by-N grid
Percolation::~Percolation()
{
    for (int i = 0; i < m_size; i++)
        delete[] m_grid[i];
    delete[] m_grid;
}

void Percolation::reset()
{
    for (int i = 0; i < m_size; i++) {
        m_grid[i] = new char[m_size];
        for (int j = 0; j < m_size; j++)
            m_grid[i][j] = stSiteBlocked;
    }
    m_virtualTopIndex = m_size*m_size;
    m_virtualBottomIndex = m_size*m_size + 1;
    m_uf->reset();
}

// open site (row i, column j) if it is not already
void Percolation::open(int i, int j)
{
    m_grid[i][j] = stSiteOpened;

    int p = linearize(i,j);

    // Top
    if (j == 0)
        m_uf->unite(p, m_virtualTopIndex);
    else
        if ( m_grid[i][j - 1] == stSiteOpened ) {
            int q = linearize(i, j - 1);
            m_uf->unite(p,q);
        }

    // Bottom
    if (j == (m_size - 1))
        m_uf->unite(p, m_virtualBottomIndex);
    else
        if (m_grid[i][j + 1] == stSiteOpened) {
            int q = linearize(i, j + 1);
            m_uf->unite(p,q);
        }

    // Left
    if (i > 0)
        if (m_grid[i - 1][j] == stSiteOpened) {
            int q = linearize(i - 1, j);
            m_uf->unite(p,q);
        }

    // Right
    if (i < (m_size -1))
        if (m_grid[i + 1][j] == stSiteOpened) {
            int q = linearize(i + 1, j);
            m_uf->unite(p,q);
        }


    return;
}

// is site (row i, column j) open?
bool Percolation::isOpen(int i, int j)
{
    if (m_grid[i][j] == stSiteOpened)
        return true;
    return false;
}
// is site (row i, column j) full?
bool Percolation::isFull(int i, int j)
{
    int index = linearize(i, j);
    // qDebug() << i << "," << j << " linear: " << index;
    // return false;
    return m_uf->connected(index, m_virtualTopIndex);
    // return false;
}

// does the system percolate?
bool Percolation::percolates()
{
    return m_uf->connected(m_virtualBottomIndex, m_virtualTopIndex);
}

int Percolation::linearize(int i, int j)
{
    return i + j*m_size;
}
