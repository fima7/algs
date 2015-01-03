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


void array_int_test(int N)
{
	cout << "Array int test\n";

	Array<int> a;

	// add
	for (int i = 0; i < N; ++i)
		a.add(i);

	// get value
	for (int i = 0; i < N; ++i)
		cout << a[i] << " ";
	cout << "\n";

	// set value
	for (int i = 0; i < N; ++i) {
		a[i] = i + 100;
		cout << a[i] << " ";
	}
	cout << "\n";

	// remove value
	for (int i = 0; i < N; ++i) {
		a.rm();
	}

	// add
	for (int i = 0; i < N; ++i)
		a.add(i);

	// get value
	for (int i = 0; i < N; ++i)
		cout << a[i] << " ";
	cout << "\n";

	cout << "Done\n";	

}

void array_object_test(int N)
{
	cout << "Array object test\n";

	Array<Object> a;

	// add
	for (int i = 0; i < N; ++i) {
		Object o(i,i);
		a.add(o);
	}

	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a[i].getValue1() << "," << a[i].getValue2() << ") ";
	cout << "\n";

	// set value
	for (int i = 0; i < N; ++i) {
		Object o(i+100,i+100);
		a[i] = o;
		cout << "(" << a[i].getValue1() << "," << a[i].getValue2() << ") ";
	}
	cout << "\n";

	// remove value
	for (int i = 0; i < N; ++i) {
		a.rm();
	}

	// add
	for (int i = 0; i < N; ++i) {
		Object o(i,i);
		a.add(o);
	}

	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a[i].getValue1() << "," << a[i].getValue2() << ") ";
	cout << "\n";

	cout << "Done\n";	
}

void array_manipulation_test(int N)
{
	cout << "Array manipulation test\n";

	Array<Object> a1, a2;

	// add
	for (int i = 0; i < N; ++i) {
		Object o(i,i);
		a1.add(o);
	}

	a2 = a1;

	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a2[i].getValue1() << "," << a2[i].getValue2() << ") ";
	cout << "\n";

	Array<Object> a3 = a2;
	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a3[i].getValue1() << "," << a3[i].getValue2() << ") ";
	cout << "\n";

	Array<Object> a4(5);
	a4 = a3;
	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a4[i].getValue1() << "," << a4[i].getValue2() << ") ";
	cout << "\n";

	Array<Object> a5;
	for (int i = 0; i < N/2; ++i) {
		Object o(i+100,i+100);
		a5.add(o);
	}
	// get value
	for (int i = 0; i < N/2; ++i)
		cout << "(" << a5[i].getValue1() << "," << a5[i].getValue2() << ") ";
	cout << "\n";

	a5 = a4;
	// get value
	for (int i = 0; i < N; ++i)
		cout << "(" << a5[i].getValue1() << "," << a5[i].getValue2() << ") ";
	cout << "\n";


	cout << "Done\n";
}

int main()
{
	/*
	for (int i = 0; i < 16; i++) {	 
		array_int_test(i);
		array_object_test(i);
		array_manipulation_test(i);
	}
	*/

	// Iterators
	Array<Object> a;
	Object o(5,5);
	a.add(o);
	a.add(o);
	/*
	Array<int>::iterator i = a.begin();
	cout <<"begin: " << (*i) << "\n";
	i++;
	cout <<"next: " << (*i) << "\n";
	*/
	
	
	for(Array<Object>::iterator i = a.begin(); i != a.end(); ++i) {
		cout << i->getValue1() << " ";
	}
	cout << "\n";













/*
	Array<Object> a;

	Object o1(1,1);
//	Object o2(5,5);

	o1.setValue1(5);
	cerr << "------------ Add first\n";	
	a.add(o1);
	o1.setValue1(7);
	cerr << "------------ Add second\n";	
	a.add(o1);

	cerr << "------------ Add third\n";	
	a.add(o1);
	cerr << "------------ Add forth\n";	
	a.add(o1);
	cerr << "------------ Done\n";	


//	a[1].setValue1(5);
//	a[1].setValue2(5);

//	cout << "value: " << a[0].getValue1() << ", " << a[0].getValue2() << "\n";
//	cout << "value: " << a[1].getValue1() << ", " << a[1].getValue2() << "\n";

//	a.rm();

*/

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
