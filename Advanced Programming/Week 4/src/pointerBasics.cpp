#include <iostream>

int main() {
	// Declare an integer variable
	int num = 42;

	// Declare a pointer variable of num
	int* ptr = &num;

	// Modify the pointer value
	*ptr = 87;

	// Print the pointer variable
	std::cout << *ptr << std::endl;

	return 0;
}
