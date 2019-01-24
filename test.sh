g++ -o random_matrix_generator.out random_matrix_generator.cpp

for i in 100 150 200 250 300
do
	for j in 1 2 3 4 5 6 7 8 9 10
	do
	./random_matrix_generator.out ${i} 10
	./test.out convolution pthread_mm 0 mat1.txt ${i} mat2.txt 10
	./test.out convolution openblas_mm 0 mat1.txt ${i} mat2.txt 10
	./test.out convolution mkl_mm 0 mat1.txt ${i} mat2.txt 10
	done

done


