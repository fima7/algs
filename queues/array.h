#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

#include <iostream>


using namespace std;

template <class T>
class Array
{
protected:
    unsigned char* m_buffer;
    int m_capacity;
	int m_size;
	void resize(int n);    
public:
    Array(int capacity = 0);
    Array(const Array<T> & other);
    virtual ~Array();
    T& operator[](int i);
    const T& operator[](int i) const; // why the first const is needed
    const Array<T>& operator=(const Array<T> & rhs);
    void add(const T & item);
    void rm();    
	int size(); // Number of elements in the array
};


//////////////// Array Implementation ///////////////////////

template <class T> 
Array<T>::Array(int capacity)
{
	m_size = 0;
    m_capacity = capacity;
    if (capacity > 0) 
        m_buffer = new unsigned char[sizeof(T)*m_capacity];
    else
        m_buffer = 0;
}

template <class T> 
Array<T>::Array(const Array<T> & other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_buffer = new unsigned char[sizeof(T)*m_capacity];
    for (int i = 0; i < m_size; i++)
		reinterpret_cast<T*>(m_buffer)[i] = reinterpret_cast<T*>(m_buffer)[i];
}

template <class T> 
Array<T>::~Array()
{
	if (m_buffer == 0)
		return;

	for (int i = 0; i < m_size; i++)
		reinterpret_cast<T*>(m_buffer)[i].~T();
	
	delete [] m_buffer;
}

template <class T> 
void Array<T>::resize(int n)
{
    unsigned char *buffer;

    cout << "resize from " << m_capacity << " to " << n << "\n"; 

    if (n > 0)
		buffer = new unsigned char[sizeof(T)*n];

    m_capacity = n;
    int min = m_capacity < m_size ? m_capacity : m_size; 

    for (int i = 0; i < min; i++) // copy objects from old array to new
		reinterpret_cast<T*>(buffer)[i] = reinterpret_cast<T*>(m_buffer)[i];

    for (int i = 0; i < m_size; i++)  // delete objects from old array
		reinterpret_cast<T*>(m_buffer)[i].~T();

	if (m_size > m_capacity) // update size when shrink array
		m_size = m_capacity;

	if (m_buffer != 0)	
		delete [] m_buffer; // initialy may not be allocated

    m_buffer = buffer;
}


template <class T> 
void Array<T>::add(const T & item)
{
	cout << "Array add to " << (void*)(m_buffer + sizeof(T) * m_size) << "\n"; 

    if (m_capacity == m_size) {
        if (Array<T>::m_capacity !=0) 
            resize(2*Array<T>::m_capacity);
        else
            resize(1);
    }

	new (m_buffer + sizeof(T) * m_size) T(item); // place the copy of item into array
	m_size++;	
}

template <class T> 
void Array<T>::rm()
{
	m_size --;
	cout << "Remove " << m_size << "th element\n";

	(reinterpret_cast<T*>(m_buffer)[m_size]).~T();
	    
    if (m_size == m_capacity/4) 
        resize(m_capacity/2); 
    
    if (m_size == 0)
        resize(0);
}

template <class T> 
int Array<T>::size()
{
	return m_size;
}


template <class T> 
T& Array<T>::operator[](int i)
{
	if ( (i < 0) || (i >= m_capacity) )
		throw std::out_of_range(string("element ") + std::to_string(i) + " while size is " + std::to_string(m_capacity));
	
    return (reinterpret_cast<T*>(m_buffer))[i];    
}

template <class T> 
const T& Array<T>::operator[](int i) const
{
	if ( (i < 0) || (i >= m_capacity) )
		throw std::out_of_range(string("element ") + std::to_string(i) 
						+ " while size is " + std::to_string(m_capacity));

   return (reinterpret_cast<T*>(m_buffer))[i];    
}


template <class T> 
const Array<T>& Array<T>::operator=(const Array<T> & rhs)
{

    if (this != &rhs) {

		for (int i = 0; i < m_size; i++) // delete own objects
			reinterpret_cast<T*>(m_buffer)[i].~T();

		if (m_buffer) 
            delete [] m_buffer;

		m_size = rhs.m_size;
		m_capacity = rhs.m_capacity;	

        m_buffer = new unsigned char[sizeof(T)*m_capacity];

		for (int i = 0; i < m_size; i++)		
			reinterpret_cast<T*>(m_buffer)[i] = reinterpret_cast<T*>(rhs.m_buffer)[i];

    }
	
    return *this;    
}

#endif
