#include <iostream>

int main() {
	// Declare a character array
	char arr1[] = "Hello, C++ Pointers!";

	// Declare a char pointer to the array
	char* strPtr = &arr1[0];

	// Iterate through the array
	for (int i = 0; arr1[i] != '\0'; i++) {
		// Print the current element
		std::cout << *strPtr << std::endl;

		// Increment the pointer
		strPtr++;
	} 

	return 0;
}
