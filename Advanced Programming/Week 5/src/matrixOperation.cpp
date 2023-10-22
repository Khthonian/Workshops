#include <iostream>

class Matrix {
private:
  int **data;
  int rows;
  int cols;

public:
  // Constructor
  Matrix(int r, int c) {
    // Initialize attributes and allocate memory for the matrix data
  }

  // Destructor
  ~Matrix() {
    // Deallocate memory for the matrix data
  }

  // Method to get value at row and col
  int get(int row, int col) {
    // Return the value at the given row and column indices
  }

  // Method to set value at row and col
  void set(int row, int col, int value) {
    // Set the value at the given row and column indices
  }

  // Method to add two matrices
  Matrix add(const Matrix &other) {
    // Implement matrix addition and return the result
  }

  // Method to multiply two matrices
  Matrix multiply(const Matrix &other) {
    // Implement matrix multiplication and return the result
  }

  // Method to display the matrix
  void display() {
    // Display the matrix elements
  }
};

int main() {
  // Input dimensions for Matrix A

  // Create Matrix A with the given dimensions

  // Input matrix elements for Matrix A

  // Input dimensions for Matrix B

  // Create Matrix B with the given dimensions

  // Input matrix elements for Matrix B

  // Display Matrix A

  // Display Matrix B

  // Perform matrix addition and display the result

  // Perform matrix multiplication and display the result

  return 0;
}
