#ifndef UNIONFIND_H
#define UNIONFIND_H

class IUnionFind
{
public:
    virtual ~IUnionFind() {} // Need to check
    virtual void reset() = 0;
    virtual void unite(int p, int q) = 0;
    virtual bool connected(int p, int q) = 0;
};

class UnionFind : public IUnionFind
{
protected:
    int* id;
    int sz;

public:
    UnionFind(int N);
    virtual ~UnionFind();
    virtual void reset();
    virtual void unite(int p, int q) = 0;
    virtual bool connected(int p, int q) = 0;
};

#endif // UNIONFIND_H
