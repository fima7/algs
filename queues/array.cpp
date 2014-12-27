#include <iostream>
#include "array.h"
#include "object.h"

using namespace std;

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
    return m_data[i];    
}

template <class T> 
const T& Array<T>::operator[](int i) const
{
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

template <class T> 
T ArrayR<T>::rm()
{
    m_size--;
    cout << "m_size: " << m_size << endl;

    T item = Array<T>::m_data[m_size];
    
    if (m_size == Array<T>::m_capacity/4) 
        resize(Array<T>::m_capacity/2); 
    
    if (m_size == 0)
        resize(0);
         
    cout << "size: " << m_size << ", capacity: " << Array<T>::m_capacity << endl;
    
    return item;
}

int main()
{

/*    
    Object b(5,7);
    Object c;

    c = a;
    a = b;


    cout << "a: " << a.getValue1() << ", " << a.getValue2() << endl;
    cout << "b: " << b.getValue1() << ", " << b.getValue2() << endl;
    cout << "c: " << c.getValue1() << ", " << c.getValue2() << endl;

    c = a = b = Object(5,5);
    cout << "a: " << a.getValue1() << ", " << a.getValue2() << endl;
    cout << "b: " << b.getValue1() << ", " << b.getValue2() << endl;
    cout << "c: " << c.getValue1() << ", " << c.getValue2() << endl;
*/
/*
   Object o(5,5);
  // Object oo = o;
   Object* a = new Object[2];
   a[0] =  o;  
   Object oo = a[0];
*/
/*

    Object o(5,5);
    ArrayR<Object> a;
    cout << "add\n";
    a.add(o); 
    cout << "rm\n";
    Object v = a.rm();
*/  
    ArrayR<int> a;

//    cout << "First \n";

    for (int i = 0; i < 10; i++) {
 //       cout << "add: " << i << endl;
        a.add(i); 
    }
    
    for (int i = 0; i < 10; i++) 
       cout << a[i] << " ";
    cout << endl;
 
    
    ArrayR<int> b;
    b = a;
    for (int i = 0; i < 10; i++) 
       cout << b[i] << " ";
    cout << endl;
 

/*
    for (int i = 0; i < 10; i++) {
        int v = a.rm(); 
        cout << "rm: " << v << endl;

    }
    cout << "Second \n";
    for (int i = 0; i < 10; i++) {
        cout << "add: " << i << endl;
        a.add(i); 
    }
    
        
    for (int i = 0; i < 10; i++) 
       cout << i << " ";
    cout << endl;
 

    for (int i = 0; i < 10; i++) {
        int v = a.rm(); 
        cout << "rm: " << v << endl;

    }
*/

    return 0;    
}

