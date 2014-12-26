
OBJ =	main.o 			\
	percolation.o		\
	percolationstats.o	\
	quickfind.o		\
	quickunioncompressed.o	\
	quickunion.o		\
	unionfind.o		\
	weightedquickunion.o	\
	stopwatch.o

percstat: $(OBJ)
	g++ -o $@ $^	


%.o : %.cpp
	g++ -c $< -o $@ 

clean:
	rm -f *.o percstat 
