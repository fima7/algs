#ifndef QUICKUNIONCOMPRESSED_H
#define QUICKUNIONCOMPRESSED_H

#include "quickunion.h"

class QuickUnionCompressed : public QuickUnion
{
protected:
    int root(int i);
public:
    QuickUnionCompressed(int N);
    virtual ~QuickUnionCompressed();
};


#endif // QUICKUNIONCOMPRESSED_H
