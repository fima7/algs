#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class Array
{
protected:
    T* m_data;
    int m_capacity;
public:
    Array(int capacity = 0);
    Array(const Array<T> & other);
    virtual ~Array();
    virtual T& operator[](int i);
    virtual const T& operator[](int i) const; // why the first const is needed
    virtual const Array<T>& operator=(const Array<T> & rhs);
};


template <class T>
class ArrayR : public Array<T>
{
private:
    int m_size;
    void resize(int n);    
public:
    ArrayR(int capacity = 0);
    ArrayR(const ArrayR<T> & other);
    const ArrayR<T>& operator=(const ArrayR<T> & rhs);
    void add(const T & item);
    T rm();    
};

#endif
