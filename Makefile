
test.out: main.o nonlinear.o probability.o pooling.o convolution.o
	g++ main.o nonlinear.o probability.o pooling.o convolution.o -o test.out

main.o: main.cpp
	g++ -c main.cpp

nonlinear.o: nonlinear.cpp nonlinear.h
	g++ -c nonlinear.cpp

probability.o: probability.cpp probability.h
	g++ -c probability.cpp


pooling.o: pooling.cpp pooling.h
	g++ -c pooling.cpp


convolution.o: convolution.cpp convolution.h
	g++ -c convolution.cpp

clean:
	rm *.o test.out	