#ifndef QUICKFIND_H
#define QUICKFIND_H

#include "unionfind.h"

class QuickFind: public UnionFind
{
public:
    QuickFind(int N);
    virtual ~QuickFind();
    void unite(int p, int q);
    bool connected(int p, int q);
};
#endif // QUICKFIND_H
