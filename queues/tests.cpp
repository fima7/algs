#include "array.h"
#include "object.h"
#include <iostream>

using namespace std;

template <class T>
class Guard
{
private:
	T* m_object;
public:
	Guard(T *o) { m_object = o;	}
	~Guard() { delete m_object;	}
	T& operator*() const { return *m_object; }
//	const T& operator*() const { return m_object; } 
	T* operator->() const { return m_object; } 
//	const T* operator->() const { return m_object; } 
};




int main()
{
	Array<Object> a(8);

	Object o(5,5);
	a.add(o);
	a.add(o);

	cout << "value: " << a[0].getValue1() << ", " << a[0].getValue2() << "\n";

	a.rm();



/*
	Guard<ArrayR<int>> a(new ArrayR<int>);
	(*a).add(5);

	try {
		cout << "element:" << (*a)[0] << "\n";	
	} catch (std::out_of_range &e) {
		cerr << "[exception] out of range: " << e.what() << "\n";
	} catch (std::exception &e) {
		cerr << "[exception] unespected: " << e.what() << "\n";
	} catch (...) {
		cerr << "[exception] unknown \n";
	}
*/

	return 0;	
}



































/*
//#include <gtest/gtest.h>

typedef ::testing::Types<int, float> ArrayTypes;

TYPED_TEST_CASE(ArrayTest, ArrayTypes);

TYPED_TEST(ArrayTest, DefaultConstructor) {
	Array<TypeParam> a;
}
	

TEST(ArrayTest, ArrayConctructors) {
	Array<int> a;
	




}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
