#ifndef QUICKUNION_H
#define QUICKUNION_H

#include "unionfind.h"

class QuickUnion: public UnionFind::UnionFind
{
protected:
    virtual int root(int i);
public:
    QuickUnion(int N);
    virtual ~QuickUnion();
    virtual void unite(int p, int q);
    bool connected(int p, int q);
};

#endif // QUICKUNION_H
