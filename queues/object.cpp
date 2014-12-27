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
    cout << "Object constructor:" << m_value << endl;

}

Object::~Object()
{
    cout << "Object delete: " << m_value << endl; 
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

Object::Object(const Object & other)
{
    m_value = new int [2];
    cout << "Object copy constructor allocate: " << m_value << endl;
    cout << "Object copy constructor: " << m_value << " <----- " << other.m_value << endl;
    m_value[0] = other.m_value[0];
    m_value[1] = other.m_value[1];    
}

Object& Object::operator=(const Object& rhs)
{
    if (this != &rhs) {
        if (m_value == 0) {
            m_value = new int [2];
            cout << "Object assignment allocate: " << m_value << endl;
        }
        cout << "Object assignment: " << m_value << " <----- " << rhs.m_value << endl;
        m_value[0] = rhs.m_value[0];
        m_value[1] = rhs.m_value[1];    
    }
    return *this;
} 

