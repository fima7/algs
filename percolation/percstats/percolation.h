#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "unionfind.h"

class Percolation
{
private:
    enum siteState {stSiteBlocked, stSiteOpened};
    int m_size;
    char **m_grid;
    IUnionFind *m_uf;
    int m_virtualTopIndex;
    int m_virtualBottomIndex;
    int linearize(int i, int j);

public:
    Percolation(int N, IUnionFind *uf);             // create N-by-N grid, with all sites blocked
    virtual ~Percolation();
    void reset();
    void open(int i, int j);     // open site (row i, column j) if it is not already
    bool isOpen(int i, int j);   // is site (row i, column j) open?
    bool isFull(int i, int j);   // is site (row i, column j) full?
    bool percolates();           // does the system percolate?
};




#endif // PERCOLATION_H
