#include <cctype>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

void factorial (int num) {
	// Declare a variable to hold the output
	int output = 1;
	// Loop through each integer until 1
	for (int count = num; count >= 1; count--) {
		// Multiply the current value by the next integer
		output *= count;	
	}
	// Return the final value
	std::cout << output << std::endl;
}

int main (int argc, char *argv[]) {
	// Validate that one argument is given
	if (argc == 2) {
		// Collect the desired argument as a string
		std::string argument = argv[1];
		
		// Declare a variable to hold the original integer
		int number;

		// Check the argument can be passed as an integer
		try {
			// Convert the argument to an integer
			number = std::stoi(argument);
		} catch (const std::exception& e) {
			// Output an error message
			std::cout << "The argument could not be converted to an integer." << std::endl;
			std::cout << "Error: " << e.what() << std::endl;
			return 1;
		}
		// Pass the argument to the factorial function
		factorial(number);
	} else {
		// Output an error message
		std::cout << "Please provide one argument e.g. ./factorial.exe 5" << std::endl;
		return 1;
	}
	return 0;
}
