#include <iostream>

int main() {
  // Declare an array of integers
  int myNums[5] = {10, 20, 30, 40, 50};

  // Declare an integer pointer for the first array element
  int *arrPtr = &myNums[0];

  // Increment the pointer to the next address
  arrPtr++;

  // Print the second element of the array before modification
  std::cout << myNums[1] << std::endl;

  // Modify the second element of the array
  *arrPtr = 25;

  // Print the second element of the array after modification
  std::cout << myNums[1] << std::endl;

  return 0;
}
