#include "quickunioncompressed.h"

QuickUnionCompressed::QuickUnionCompressed(int N) : QuickUnion(N)
{
}

QuickUnionCompressed::~QuickUnionCompressed()
{
}

int QuickUnionCompressed::root(int i)
{
    // Just after computing the root of p, set the id of each examined node to point to that root.

    // int root = QuickUnion::root(i);
    // id[i] = root;

    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

