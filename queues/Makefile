LDFLAGS := -lgtest -lgtest_main -L/usr/lib -lpthread 

OBJ =	object.o

tests: $(OBJ) tests.o
	g++ -o $@ $^

#	g++ -o $@ $^ $(LDFLAGS) 



array: $(OBJ)
	g++ -o $@ $^	

%.o : %.cpp
	g++ -std=c++11 -c $< -o $@ 

clean:
	rm -f *.o tests
