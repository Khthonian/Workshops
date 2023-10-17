#include <iostream>

int main() {
  // Declare an integer array
  int arr1[5] = {10, 20, 30, 40, 50};

  // Declare an integer pointer to the third element of the array
  int *intPtr = &arr1[2];

  // Select and print the second element
  intPtr--;
  std::cout << *intPtr << std::endl;

  // Select and print the fourth element
  intPtr += 2;
  std::cout << *intPtr << std::endl;

  return 0;
}
