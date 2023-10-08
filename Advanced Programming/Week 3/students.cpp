#include <iostream>
#include <stdexcept>

class Student {
	public:
		// Constructor
		Student() {
			// Empty default constructor
		}

		// Score constructor
		Student(int newScore) {
			// Assign the user input to the class variable
			score = newScore;
		}

		// Declare a function to return the score
		int getScore() {
			return score;
		}

	private:
		// Declare the score variable
		int score;
};

int main (int argc, char *argv[]) {
	// Declare an array to hold the Student objects
	Student students[10];
	
	// Declare a temp variable to hold the input score
	int tempScore;

	// Loop 10 times to add each student
	for (int i = 0; i < 10; i++) {

		// Error catching in case a user has an invalid input
		try {
			// Print a prompt for the user to give a score
			std::cout << "Enter score for student " << (i + 1) << ": ";
			std::cin >> tempScore;
		} catch (const std::invalid_argument& e) {
			std::cerr << "Invalid input! Please enter a valid integer." << std::endl;
			return 1;
		} catch (const std::out_of_range& e) {
			std::cerr << "Input is out of range for an integer." << std::endl;
			return 1;
		}

		// Initialise the current student with the temp score
		students[i] = Student(tempScore);
	}

	// Initialise variables to hold the calculated info
	int totalStudents = 10;
	float averageScore;
	int highScore = 0;
	int lowScore = 100;
	int aboveAverage = 0;
	int belowAverage = 0;

	// Loop through each student score and calculate the average score
	for (int i = 0; i < 10; i++) {
		averageScore += students[i].getScore();	
	}
	
	// Divide the sum by the total number of students
	averageScore /= totalStudents;

	// Loop through each student score and calculate the remaining information
	for (int i = 0; i < 10; i++) {
		// Check for new high score
		if (students[i].getScore() >= highScore) {
			highScore = students[i].getScore();
		}

		// Check for new low score
		if (students[i].getScore() <= lowScore) {
			lowScore = students[i].getScore();
		}
		
		// Check if score is above average
		if (students[i].getScore() > averageScore) {
			aboveAverage += 1;
		}

		// Check if score is above average
		if (students[i].getScore() < averageScore) {
			belowAverage += 1;
		}

	}

	// Print the information to the console
	std::cout << std::endl;
	std::cout << "Total students: " << totalStudents << std::endl;
	std::cout << "Average score: " << averageScore << std::endl;
	std::cout << "Highest score: " << highScore << std::endl;
	std::cout << "Lowest score: " << lowScore << std::endl;
	std::cout << "Students above average: " << aboveAverage << std::endl;
	std::cout << "Students below average: " << belowAverage << std::endl;

	return 0;
}								
