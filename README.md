# Matrix Multiplication with Threading (C)

This project demonstrates matrix multiplication using two threading approaches in C for parallel computation. It reads two input matrices from a file, performs matrix multiplication, and prints the result alongside the computation time for each method.
Features

    Element-wise Threading: Each element of the result matrix is computed in its own thread.
    Row-wise Threading: Each row of the result matrix is computed in a separate thread.
    Input & Output: The program reads input matrices from a file and prints the resulting matrix along with the elapsed time for each computation method.

 # Files

    7497-matrix.c: The main source code for matrix multiplication using threads.
    matrices.txt: The input file containing two matrices for multiplication.
    7497-matrix: The compiled executable for running the program.

# How to Run

    Clone the Repository: Clone this repository to your local machine using the following command:

git clone https://github.com/your-username/7497-lab4.git

Compile the Code: Navigate to the project directory and compile the C program:

gcc 7497-matrix.c -o 7497-matrix -lpthread

Run the Program: After compilation, you can run the program as follows:

./7497-matrix

Input Format: The program expects the input matrices in the following format in matrices.txt:

[number of rows of 1st matrix] [number of columns of 1st matrix]
1st matrix entries
[number of rows of 2nd matrix] [number of columns of 2nd matrix]
2nd matrix entries

Output Format: The program prints the resulting matrix and the computation time for both threading methods:

    [result matrix entries]
    END1 [elapsed time of procedure 1]
    [result matrix entries]
    END2 [elapsed time of procedure 2]

# Example
Input (matrices.txt):

3 5
1 -2 3 4 5
-1 2 3 4 5
5 4
-1 2 3 4
1 -2 3 4
1 2 -3 4
1 2 3 -4
-1 -2 -3 -4

Output:

-1 10 -15 -28
-3 -10 15 -36
5 -2 -9 -20
END1 0.006788
-1 10 -15 -28
-3 -10 15 -36
5 -2 -9 -20
END2 0.000202

# Performance

The program compares two threading strategies based on computation time:

    Element-wise threading computes each element in a separate thread.
    Row-wise threading computes each element in a separate thread.
    Row-wise threading computes each row in a separate thread, typically resulting in faster execution due to reduced thread overhead.

