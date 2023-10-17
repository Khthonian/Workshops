#include <iostream>

int main() {
  // Declare an integer variable
  int num1 = 100;

  // Declare a pointer to the address of num1
  int *ptr1 = &num1;

  // Declare a pointer to the address of ptr1
  int **ptr2 = &ptr1;

  // Print the value of num1 before modification
  std::cout << num1 << std::endl;

  // Modify ptr2
  **ptr2 = 200;

  // Print the value of num1 after modification
  std::cout << num1 << std::endl;

  return 0;
}
