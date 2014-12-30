#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

#include <iostream>


using namespace std;

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
    virtual T& operator[](int i);
    virtual const T& operator[](int i) const; // why the first const is needed
    const ArrayR<T>& operator=(const ArrayR<T> & rhs);
    void add(const T & item);
    void rm();    
};


//////////////// Array Implementation ///////////////////////

template <class T> 
Array<T>::Array(int capacity)
{
    m_capacity = capacity;
    if (capacity > 0)
        m_data = new T[m_capacity];
    else
        m_data = 0;
}

template <class T> 
Array<T>::~Array()
{
    if (m_data)
        delete [] m_data;
}

template <class T> 
T& Array<T>::operator[](int i)
{
	if ( (i < 0) || (i >= m_capacity) )
		throw std::out_of_range(string("element ") + std::to_string(i) + " while size is " + std::to_string(m_capacity));
    return m_data[i];    
}

template <class T> 
const T& Array<T>::operator[](int i) const
{
	if ( (i < 0) || (i >= m_capacity) )
		throw std::out_of_range(string("element ") + std::to_string(i) 
						+ " while size is " + std::to_string(m_capacity));
   return m_data[i];    
}

template <class T> 
Array<T>::Array(const Array<T> & other)
{
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++)
        m_data[i] = other.m_data[i];      
}


template <class T> 
const Array<T>& Array<T>::operator=(const Array<T> & rhs)
{
    if (this != &rhs) {
        m_capacity = rhs.m_capacity;
        if (m_data) 
            delete [] m_data;
        m_data = new T [m_capacity];
        for (int i = 0; i < m_capacity; i++)
            m_data[i] = rhs.m_data[i];      
    }
    return *this;    
}

//////////////// ArrayR Implementation ///////////////////////

// Resizibale
template <class T> 
ArrayR<T>::ArrayR(int capacity) : Array<T>(capacity)
{
    m_size = Array<T>::m_capacity;    
}

template <class T> 
ArrayR<T>::ArrayR(const  ArrayR<T> & other)
{
    Array<T>::m_capacity = other.m_capacity;
    Array<T>::m_data = new T[Array<T>::m_capacity];
    m_size = other.m_size;
    for (int i = 0; i < m_size; i++) // size, not capacity
        Array<T>::m_data[i] = other.m_data[i];      
}

template <class T> 
const  ArrayR<T>& ArrayR<T>::operator=(const ArrayR<T> & rhs)
{
     if (this != &rhs) {
        Array<T>::m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        if (Array<T>::m_data) 
            delete [] Array<T>::m_data;
        Array<T>::m_data = new T [Array<T>::m_capacity];
        for (int i = 0; i < m_size; i++)
            Array<T>::m_data[i] = rhs.m_data[i];      
    }
    return *this;    
}

template <class T> 
T& ArrayR<T>::operator[](int i)
{
	if ( (i < 0) || (i >= m_size) ) // size, not capacity
		throw std::out_of_range(string("element ") + std::to_string(i) 
						+ " while size is " + std::to_string(m_size));
    return Array<T>::m_data[i];    
}

template <class T> 
const T& ArrayR<T>::operator[](int i) const
{
	if ( (i < 0) || (i >= m_size) ) // size, not capacity
		throw std::out_of_range(string("element ") + std::to_string(i) + " while size is " + std::to_string(m_size));
   return Array<T>::m_data[i];    
}



template <class T> 
void ArrayR<T>::resize(int n)
{
    T* new_data = 0;

    cout << "resize from " << Array<T>::m_capacity << " to " << n << "\n"; 

    if (n > 0)
        new_data = new T[n];

    Array<T>::m_capacity = n;
    int min = Array<T>::m_capacity < m_size ? Array<T>::m_capacity : m_size; 
    for (int i = 0; i < min; i++)
        new_data[i] = Array<T>::m_data[i];
    delete [] Array<T>::m_data; // initialy may not be allocated

    Array<T>::m_data = new_data;
}

template <class T> 
void ArrayR<T>::add(const T & item)
{
    if (Array<T>::m_capacity == m_size) {
        if (Array<T>::m_capacity !=0) 
            resize(2*Array<T>::m_capacity);
        else
            resize(1);
    }
    Array<T>::m_data[m_size++] = item;
    cout << "size: " << m_size << ", capacity: " << Array<T>::m_capacity << endl;
}


// Return void, get by reference with [], to avoid copy
template <class T> 
void ArrayR<T>::rm()
{
    m_size--;
    cout << "m_size: " << m_size << endl;

	// free item data assigning an empty item
	T item;
    Array<T>::m_data[m_size] = item; 
    
    if (m_size == Array<T>::m_capacity/4) 
        resize(Array<T>::m_capacity/2); 
    
    if (m_size == 0)
        resize(0);
         
    cout << "size: " << m_size << ", capacity: " << Array<T>::m_capacity << endl;
    
}

#endif
