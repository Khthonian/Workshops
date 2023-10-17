#include <iostream>
#include <ostream>

int main() {
  // Declare an integer pointer
  int *dynamicInt;

  // Dynamically allocate memory for an integer
  dynamicInt = new int;

  // Validate the memory allocation
  if (dynamicInt == nullptr) {
    std::cerr << "Failed memory allocation!" << std::endl;
    return 1;
  }

  // Prompt the user for an integer input
  std::cout << "Enter an integer: ";
  int userInput;
  std::cin >> userInput;

  // Store the user input in the allocated memory
  *dynamicInt = userInput;

  // Print the stored value
  std::cout << "Stored value: " << *dynamicInt << std::endl;

  // Deallocate the memory
  delete dynamicInt;

  return 0;
}
