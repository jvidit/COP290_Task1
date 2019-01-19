Functions and how to call them from command line:

convolution
	./test convolution <type_of_convolution(normal/matrix_mult)> <padsize> <matrix1.txt> <matrix1_numrows> <matrix2.txt> <matrix2_numrows> 
	<type_of_convolution(normal/matrix_mult)>: matrix_mult for convolution after Toeplitzation and using matrix multiplication, normal o/w
	<padsize>: whole number input padding size, 0 if no padding
	<matrix1.txt>: .txt file containing the input square matrix in column major order in the same directory
	<matrix1_numrows>: size of input matrix
	<matrix2.txt>: .txt file containing the square kernel in the same directory, kernel gets flipped before applying convolution
	<matrix2_numrows>: size of kernel, must be smaller than <matrix1_numrows>
	The result gets stored in ans.txt in row major order in the same directory

relu
	./test relu <matrix.txt> <matrix_numrows> <matrix_numcolums>
	<matrix.txt>: .txt file containing the input matrix in column major order in the same directory
	<matrix_numrows>: row size of input matrix
	<matrix_numcolumns>: column size of input matrix
	The result gets stored in ans.txt in the same directory

tanh
	./test tanh <matrix.txt> <matrix_numrows> <matrix_numcolumns>
	<matrix.txt>: .txt file containing the input matrix in column major order in the same directory
	<matrix_numrows>: row size of input matrix
	<matrix_numcolumns>: column size of input matrix
	The result gets stored in ans.txt in the same directory

pooling
	./test pooling <pool_type(max/avg)> <stride> <matrix.txt> <matrix_numrows>
	<pool_type(max/avg)>: max for max pooling, avg for average pooling
	<stride>: non-overlapping stride value, should be a divisor of <matrix_numrows>
	<matrix.txt>: .txt file containing the input square matrix in column major order in the same directory
	<matrix_numrows>: size of input matrix
	The result gets stored in ans.txt in row major order in the same directory

softmax
	./test softmax <vector_length> <vector.txt>
	<vector_length>: size of input vector
	<vector.txt>: .txt file containing the input vector in the same directory
	The result gets stored in ans.txt in the same directory
	
sigmoid
	./test sigmoid <vector_length> <vector.txt>
	<vector_length>: size of input vector
	<vector.txt>: .txt file containing the input vector in the same directory
	The result gets stored in ans.txt in the same directory
	



