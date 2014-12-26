#include "weightedquickunion.h"
#include "quickunion.h"

WeightedQuickUnion::WeightedQuickUnion(int N) : QuickUnion(N)
{
    TreeSize = new int[N];
    TreeSizeSz = N;
    this->reset();
}


WeightedQuickUnion::~WeightedQuickUnion()
{
    delete [] TreeSize;
}

void WeightedQuickUnion::reset()
{
    UnionFind::reset();
    for (int i = 0; i < TreeSizeSz; i++)
        TreeSize[i] = 1;
}

void WeightedQuickUnion::unite(int p, int q)
{
    int p_root = root(p);
    int q_root = root(q);

    if (TreeSize[p_root] < TreeSize[q_root]) {
        id[p_root] = q_root;
        TreeSize[q_root] += TreeSize[p_root];
    } else {
        id[q_root] = p_root;
        TreeSize[p_root] += TreeSize[q_root];
    }
}

WeightedQuickUnionCompressed::WeightedQuickUnionCompressed(int N) : WeightedQuickUnion(N)
{

}

WeightedQuickUnionCompressed::~WeightedQuickUnionCompressed()
{

}

int WeightedQuickUnionCompressed::root(int i)
{
    // int root = QuickUnion::root(i);
    // id[i] = root;
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
