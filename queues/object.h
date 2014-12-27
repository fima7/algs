#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
    int* m_value;
public:
    Object();
    Object(int v1, int v2);
    Object(const Object & other);
    virtual ~Object();
    int getValue1();
    int getValue2();
    Object& operator=(const Object& rhs); 

};

#endif
