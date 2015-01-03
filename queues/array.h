#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>
// #include "iterator.h"

// #include <iostream>
using namespace std;

template <class T>
class Array 
{
protected:
    unsigned char* m_buffer;
    int m_capacity;
	int m_size;
	void resize(int n);
//	void swap(Array<T>& other);
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

	class iterator 
	{
	private:
		T *m_current;
		int m_position;
	public:	
		iterator(T *current, int position) : m_current(current), m_position(position){}
		iterator& operator =(const iterator& other) {
			if (this != &other)	{
				m_current = other.m_current;
				m_position = other.m_position;
			}
			return *this;		
		}
		T& operator*() { return *m_current; }
		T* operator->() { return m_current; }

		const iterator& operator++() {
			++m_current;
			++m_position;
			return *this;			
		}
		iterator operator++(int) {
			iterator tmp(m_current);
			++m_current;
			++m_position;
			return tmp;			
		}
		bool operator == (iterator const& i) { return m_position == i.m_position; }
		bool operator != (iterator const& i) { return !(m_position == i.m_position);  }
	};
	iterator begin() { return iterator( reinterpret_cast<T*>(m_buffer),      0); }
	iterator end()   { return iterator( reinterpret_cast<T*>(m_buffer), m_size); }
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
    for (int i = 0; i < m_size; i++) {
		*(new (m_buffer + sizeof(T) * i) T()) = (reinterpret_cast<T*>(other.m_buffer)[i]); 
		// (reinterpret_cast<T*>(m_buffer)[i]) = (reinterpret_cast<T*>(other.m_buffer)[i]); // VPTR copy issue
	}
}

template <class T> 
Array<T>::~Array()
{
	if (m_buffer == 0)
		return;

	for (int i = m_size - 1; i > -1; i--) {
		// cerr << "Delete size " << sizeof(T) << ": ";
		// cerr << &(reinterpret_cast<T*>(m_buffer)[i]);
		// cerr << "\n";	
		(reinterpret_cast<T*>(m_buffer)[i]).~T();
	}
	
	delete [] m_buffer;
}

// #include <cstring>

template <class T> 
void Array<T>::resize(int n)
{
    unsigned char *buffer = 0;

//    cerr << "resize from " << m_capacity << " to " << n << "\n"; 

    if (n > 0) {
		buffer = new unsigned char[sizeof(T)*n];
		// cerr << "New buffer size " <<  sizeof(T)*n << ": " << (void*)buffer << "\n";
	}

    m_capacity = n;
    int min = m_capacity < m_size ? m_capacity : m_size; 

    for (int i = 0; i < min; i++) { // copy objects from old array to new
		// cerr << "Copy from " << &(reinterpret_cast<T*>(m_buffer)[i]) << " to ";
		// cerr << &(reinterpret_cast<T*>(buffer)[i]) << " \n";
	
		// construct object in memory block
		// works: create VPTR, copy data using copy constructor (deep copy) 
		*(new (buffer + sizeof(T) * i) T()) = (reinterpret_cast<T*>(m_buffer)[i]); 

		// fails: raw copy with VPTR, looses data (shallow copy)
		// memcpy( (reinterpret_cast<T*>(buffer)+i), (reinterpret_cast<T*>(m_buffer)+i), sizeof(T) );	
		
		// fails: doesn't copy VPTR, copy data using copy constructor (deep copy) 
		// (reinterpret_cast<T*>(buffer)[i]) = (reinterpret_cast<T*>(m_buffer)[i]);						

		/*
		cout << "Old VPTR\n";	
		vptr_print( (reinterpret_cast<T*>(m_buffer)[i]) );
		
		cout << "New VPTR\n";	
		vptr_print( (reinterpret_cast<T*>(buffer)[i]) );
		*/
	}


   	for (int i = m_size - 1; i > -1; i--) { // delete objects from old array
		// cerr << "Delete: " << &(reinterpret_cast<T*>(m_buffer)[i]) << "\n";
		(reinterpret_cast<T*>(m_buffer)[i]).~T();

	}


	if (m_buffer != 0) {	
		// cerr << "Delete old m_buffer: " << (void*)m_buffer << "\n";
		delete [] m_buffer; // initialy may not be allocated
	}
		
    m_buffer = buffer;
}


template <class T> 
void Array<T>::add(const T & item)
{

    if (m_capacity == m_size) {

        if (m_capacity !=0) 
            resize(2*m_capacity);
        else
            resize(1);
    }

	// cerr << "New place " << (void*)(m_buffer + sizeof(T) * m_size) << "\n"; 

	new (m_buffer + sizeof(T) * m_size) T(item); // place the copy of item into array


	if (m_size > m_capacity) 
		m_size = m_capacity; // shrink
	else
		m_size++;			// enlarge
}

template <class T> 
void Array<T>::rm()
{
	m_size --;
	// cerr << "Remove " << m_size << "th element\n";

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
	
    return (reinterpret_cast<T*>(m_buffer)[i]);    
}

template <class T> 
const T& Array<T>::operator[](int i) const
{
	if ( (i < 0) || (i >= m_capacity) )
		throw std::out_of_range(string("element ") + std::to_string(i) 
						+ " while size is " + std::to_string(m_capacity));

   return (reinterpret_cast<T*>(m_buffer)[i]);    
}


template <class T> 
const Array<T>& Array<T>::operator=(const Array<T> & rhs)
{

    if (this != &rhs) {

		for (int i = 0; i < m_size; i++) // delete own objects
			(reinterpret_cast<T*>(m_buffer)[i]).~T();

		if (m_buffer != 0) 
            delete [] m_buffer;

		m_size = rhs.m_size;
		m_capacity = rhs.m_capacity;	

        m_buffer = new unsigned char[sizeof(T)*m_capacity];

		for (int i = 0; i < m_size; i++) {		
			*(new (m_buffer + sizeof(T) * i) T()) = (reinterpret_cast<T*>(rhs.m_buffer)[i]); 
			// (reinterpret_cast<T*>(m_buffer)[i]) = (reinterpret_cast<T*>(rhs.m_buffer)[i]); // VPTR issue
		}

    }
	
    return *this;    
}


/*
void Array<T>::swap(Array<T>& other)
{
	
	using std::swap;

	swap(m_buffer, other.m_buffer);
	swap(m_size, other.m_size);
	swap(m_capacity, other.m_capacity);
	
}
*/

#endif
