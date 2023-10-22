#include <iostream>

class Matrix {
private:
  int **data;
  int rows;
  int cols;

public:
  // Constructor
  Matrix(int r, int c) {
    // Initialise attributes
    rows = r;
    cols = c;

    // Allocate memory for the matrix data
    data = new int *[rows];
    for (int i = 0; i < rows; i++) {
      data[i] = new int[cols];
    }
  }

  // Destructor
  ~Matrix() {
    // Deallocate memory for the matrix data
    for (int i = 0; i < rows; i++) {
      delete[] data[i];
    }
    delete[] data;
  }

  // Method to get value at row and col
  int get(int row, int col) const {
    // Return the value at the given row and column indices
    return data[row][col];
  }

  // Method to set value at row and col
  void set(int row, int col, int value) {
    // Set the value at the given row and column indices
    data[row][col] = value;
  }

  // Method to add two matrices
  Matrix add(const Matrix &other) {
    // Validate row and column equality
    if (rows != other.rows || cols != other.cols) {
      std::cout << "Matrix dimensions do not allow for addition!" << std::endl;
      std::cout << std::endl;
    }

    // Declare a new Matrix object
    Matrix C(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        C.set(i, j, get(i, j) + other.get(i, j));
      }
    }
    return C;
  }

  // Method to multiply two matrices
  Matrix multiply(const Matrix &other) {
    // Validate column equality
    if (cols != other.rows) {
      std::cout << "Matrix dimensions do not allow for multiplication!"
                << std::endl;
      std::cout << std::endl;
    }

    // Declare a new Matrix object
    Matrix C(rows, other.cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < other.cols; j++) {
        int product = 0;
        for (int k = 0; k < cols; k++) {
          product += get(i, k) * other.get(k, j);
        }
        C.set(i, j, product);
      }
    }
    return C;
  }

  // Method to display the matrix
  void display() const {
    // Display the matrix elements
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout << get(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  // Input dimensions for Matrix A
  int rowsA, colsA;
  std::cout << "Enter the number of rows and columns for Matrix A: ";
  std::cin >> rowsA >> colsA;

  // Create Matrix A with the given dimensions
  Matrix matrixA(rowsA, colsA);

  // Input matrix elements for Matrix A
  std::cout << "Enter elements for Matrix A:" << std::endl;
  for (int i = 0; i < rowsA; ++i) {
    for (int j = 0; j < colsA; ++j) {
      int value;
      std::cout << "Element (" << i + 1 << "," << j + 1 << "): ";
      std::cin >> value;
      matrixA.set(i, j, value);
    }
  }

  std::cout << std::endl;

  // Input dimensions for Matrix B
  int rowsB, colsB;
  std::cout << "Enter the number of rows and columns for Matrix B: ";
  std::cin >> rowsB >> colsB;

  // Create Matrix B with the given dimensions
  Matrix matrixB(rowsB, colsB);

  // Input matrix elements for Matrix A
  std::cout << "Enter elements for Matrix B:" << std::endl;
  for (int i = 0; i < rowsB; ++i) {
    for (int j = 0; j < colsB; ++j) {
      int value;
      std::cout << "Element (" << i + 1 << "," << j + 1 << "): ";
      std::cin >> value;
      matrixB.set(i, j, value);
    }
  }

  std::cout << std::endl;

  // Display Matrix A
  std::cout << "Matrix A:" << std::endl;
  matrixA.display();

  std::cout << std::endl;

  // Display Matrix B
  std::cout << "Matrix B:" << std::endl;
  matrixB.display();

  std::cout << std::endl;

  // Perform matrix addition and display the result
  Matrix matrixC = matrixA.add(matrixB);
  std::cout << "Matrix A + Matrix B:" << std::endl;
  matrixC.display();

  std::cout << std::endl;

  // Perform matrix multiplication and display the result
  Matrix matrixD = matrixA.multiply(matrixB);
  std::cout << "Matrix A * Matrix B:" << std::endl;
  matrixD.display();

  return 0;
}
