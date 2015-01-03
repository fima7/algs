CFLAGS := -g
LDFLAGS := -lgtest -lgtest_main -L/usr/lib -lpthread 

OBJ =	object.o tests.o

tests: $(OBJ)
	g++ -o $@ $^

#	g++ -o $@ $^ $(LDFLAGS) 



array: $(OBJ)
	g++ -o $@ $^	

%.o : %.cpp
	g++ $(CFLAGS) -std=c++11 -c $< -o $@ 

clean:
	rm -f *.o tests
