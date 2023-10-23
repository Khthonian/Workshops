# Matrices
## Problem Statement
"You are tasked with writing a C++ program that performs basic matrix operations, including addition and multiplication. Your program should demonstrate your understanding of dynamic memory allocation, pointer arithmetic, and matrix manipulation."

## The Matrix Class
### The Constructor Function
The constructor function for the `Matrix` class takes in two integer values, `r` and `c`, and assigns the values to the private variables of `rows` and `cols` respectively. `rows` and `cols` are used to store the dimensions of the matrix, and are useful for validating whether an addition or multiplication operation is viable with a corresponding matrix.

The `data` variable is used to dynamically assign memory and store the data within the matrix. `data` is initialised with an array of integer pointers, with a pointer for each row. The for loop then iterates through each row pointer and assigns an array of integers. Using the `new` operator returns a pointer to both of the arrays.

### The Destructor Function
The destructor function operates in the reverse order to the constructor function. It begins by iterating through each row pointer and deallocating the memory. After each row pointer has been deallocated, the memory storing the matrix is then deallocated.

## Calculating the Matrix Operations
### The `add` Function
In order for two matrices to be added together, they must have the same dimensions. A if statement has been used to validate the row and column equality between the matrices.

```cpp
if (rows != other.rows || cols != other.cols) {
    std::cout << "Matrix dimensions do not allow for addition!" << std::endl;
    std::cout << std::endl;
}
```

In order to return a resulting matrix, a new matrix `C` is made with the same dimensions as the addend matrices, using `rows` and `cols`. A nested for loop is used to iterate through each row and column position and use the `set` member function to assign the value of the matrix position as the sum of the addends. The resulting matrix `C` is then returned.

```cpp
C.set(i, j, get(i, j) + other.get(i, j));
```

### The `multiply` Function
Similar to the addition of matrices, the number of columns of the first factor matrix must be equal to the number of rows in the second factor matrix. A similar validation check is implemented to check for row-column equality between the matrices.

As in the `add` function, a new matrix `C` is declared but with the row dimensions of the first factor and the column dimension of the second aA nested for loop with a depth of 3 is used to iterate through the rows of the first factor, the columns of the second factor, and then the columns of the first factor. Within the second for loop, an integer variable `product` is declared with a value of 0, to be used to store the final product for the respective matrix position. In the third for loop, the product of the partial product is added to the final product. Again, the resulting matrix `C` is returned once all products have been calculated. 
