#include "quickunion.h"
#include "unionfind.h"

QuickUnion::QuickUnion(int N) : UnionFind(N)
{

}

void QuickUnion::unite(int p, int q)
{
    int p_root = root(p);
    int q_root = root(q);
    id[p_root] = q_root;// id[q_root]; // q_root could be used
}

bool QuickUnion::connected(int p, int q)
{
    if (root(q) == root(p))
        return true;
    return false;
}

QuickUnion::~QuickUnion()
{


}

int QuickUnion::root(int i)
{
    while (i != id[i])
        i = id[i];        
    return i;
}

