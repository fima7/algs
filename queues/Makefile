
OBJ =	array.o object.o

array: $(OBJ)
	g++ -o $@ $^	


%.o : %.cpp
	g++ -c $< -o $@ 

clean:
	rm -f *.o array 
