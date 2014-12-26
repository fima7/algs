#include "quickfind.h"
#include "unionfind.h"

QuickFind::QuickFind(int N) : UnionFind(N)
{

}

void QuickFind::unite(int p, int q)
{
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < sz; i++)
        if (id[i] == pid)
            id[i] = qid;
}

bool QuickFind::connected(int p, int q)
{
    if (id[p] == id[q])
        return true;
    return false;
}

QuickFind::~QuickFind() {

}

