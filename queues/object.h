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
    Object(Object & other);
    virtual  ~Object();
    int getValue1();
    int getValue2();
    void setValue1(int v);
    void setValue2(int v);
    Object& operator=(const Object& rhs); 

};

void vptr_print(Object& obj);
#endif
