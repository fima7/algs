#include "unionfind.h"

#include <QDebug>

UnionFind::UnionFind(int N) {
    sz = N;
    id = new int[N];
    for (int i = 0; i < sz; i++)
        id[i] = i;

    // this->reset();
}

UnionFind::~UnionFind() {
    delete[] id;
}

void UnionFind::reset()
{
    qDebug() << "Reset UnionFind: " << sz;
    for (int i = 0; i < sz; i++)
        id[i] = i;
}

