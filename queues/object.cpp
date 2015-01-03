#include "object.h"
#include <iostream>

using namespace std;

Object::Object()
{
    m_value = 0;    
    cout << "Object default constrictor:" << m_value << "\n";
}


Object::Object(int v1, int v2)
{
    m_value = new int [2];
    m_value[0] = v1;
    m_value[1] = v2;    
    cout << "Object constructor:" << this << endl;

}

Object::~Object()
{
    cerr << "Object delete: " << this << endl; 
    delete [] m_value;
}

int Object::getValue1()
{
    return m_value[0];    
}

int Object::getValue2()
{
    return m_value[1];
}

void Object::setValue1(int v)
{
	m_value[0] = v;	
}

void Object::setValue2(int v)
{
	m_value[1] = v;	
}

 
Object::Object(const Object & other)
{
	if (other.m_value != 0) {
	    m_value = new int [2];
	    cout << "Object copy constructor allocate: " << this << endl;
	    cout << "Object copy constructor: " << this << " <----- " << &other << endl;
	    m_value[0] = other.m_value[0];
	    m_value[1] = other.m_value[1];    
	}
}

Object::Object(Object & other)
{
	if (other.m_value != 0) {
	    m_value = new int [2];
	    cout << "Object copy constructor allocate: " << this << endl;
	    cout << "Object copy constructor: " << this << " <----- " << &other << endl;
	    m_value[0] = other.m_value[0];
	    m_value[1] = other.m_value[1];    
	}
}


Object& Object::operator=(const Object& rhs)
{
    if (this != &rhs) {
        if (m_value == 0) {
            m_value = new int [2];
            cout << "Object assignment allocate: " << this << endl;
        }
        cout << "Object assignment: " << this << " <----- " << &rhs << endl;
        m_value[0] = rhs.m_value[0];
        m_value[1] = rhs.m_value[1];    
    }
    return *this;
}

void vptr_print(Object& obj)
{
	cout << "VPTR's Address " << (int*)(&obj+0) << endl;
	int addr = *(int*)(&obj+0);
	cout << " VIRTUAL TABLE 's Address " << addr << endl;
}

 

