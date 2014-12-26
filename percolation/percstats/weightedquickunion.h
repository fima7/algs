#ifndef WEIGHTEDQUICKUNION_H
#define WEIGHTEDQUICKUNION_H

#include "quickunion.h"
#include "quickunioncompressed.h"

class WeightedQuickUnion : public QuickUnion
{
private:
    int* TreeSize;
    int TreeSizeSz;

public:
    WeightedQuickUnion(int N);
    virtual ~WeightedQuickUnion();
    void reset();
    void unite(int p, int q);
};

class WeightedQuickUnionCompressed : public WeightedQuickUnion
{
protected:
    int root(int i);
public:
    WeightedQuickUnionCompressed(int N);
    virtual ~WeightedQuickUnionCompressed();
};



#endif // WEIGHTEDQUICKUNION_H
