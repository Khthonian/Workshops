#include <iostream>

// Declare a function that takes two pointers and swaps the values
void swapValues(int *ptr1, int *ptr2) {
  // Declare a swap pointer
  int *ptr3;

  *ptr3 = *ptr2;
  *ptr2 = *ptr1;
  *ptr1 = *ptr3;
}

int main() {
  // Declare two integer variables
  int num1 = 10;
  int num2 = 20;

  // Print the values of the variables
  std::cout << num1 << std::endl;
  std::cout << num2 << std::endl;

  // Swap the values
  swapValues(&num1, &num2);

  // Print the values of the swapped variables
  std::cout << num1 << std::endl;
  std::cout << num2 << std::endl;

  return 0;
}
